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

 /* 连接或重新连接完成后的回调函数 (适用于基于异步API的委托通道和回报通道) */
static int32    _MdsClientApi_OnAsyncConnect(
	MdsAsyncApiChannelT *pAsyncChannel,
	void *pCallbackParams);

/* 连接断开后的回调函数 (适用于基于异步API的委托通道和回报通道) */
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

/* 对接收到的回报消息进行处理的回调函数 */
static int32    _MdsClientApi_HandleReportMsg(
	MdsApiSessionInfoT *pRptChannel,
	SMsgHeadT *pMsgHead,
	void *pMsgBody,
	void *pCallbackParams);

/* 对接收到的应答消息进行处理的回调函数 (适用于委托通道) */
static int32    _MdsClientApi_HandleOrderChannelRsp(
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
	_pDefaultOrdChannel = NULL;
	_pDefaultRptChannel = NULL;
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
			pCfgFile, MdsAPI_CFG_DEFAULT_SECTION_LOGGER);
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
	MdsAsyncApiChannelT     *pOrdChannel = (MdsAsyncApiChannelT *)NULL;
	MdsAsyncApiChannelT     *pRptChannel = (MdsAsyncApiChannelT *)NULL;

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
	pAsyncContext = MdsAsyncApiContextT(pCfgFile);
	if (!pAsyncContext) {
		SLOG_ERROR("创建异步API的运行时环境失败!");
		return FALSE;
	}

	/* 添加初始的委托通道 */
	if (_apiCfg.ordChannelCfg.addrCnt > 0) {
		pOrdChannel = MdsAsyncApi_AddChannel(
			pAsyncContext, MDSAPI_CHANNEL_TYPE_ORDER,
			MdsAPI_CFG_DEFAULT_KEY_ORD_ADDR, &_apiCfg.ordChannelCfg,
			(OesApiSubscribeInfoT *)NULL,
			_MdsClientApi_HandleOrderChannelRsp, _pSpi,
			_MdsClientApi_OnAsyncConnect, _pSpi,
			_MdsClientApi_OnAsyncDisconnect, _pSpi);
		if (__spk_unlikely(!pOrdChannel)) {
			SLOG_ERROR("添加委托通道失败! channelTag[%s]",
				MdsAPI_CFG_DEFAULT_KEY_ORD_ADDR);
			MdsAsyncApi_ReleaseContext(pAsyncContext);
			return FALSE;
		}
	}

	/* 添加初始的回报通道 */
	if (_apiCfg.rptChannelCfg.addrCnt > 0) {
		pRptChannel = MdsAsyncApi_AddChannel(
			pAsyncContext, MDSAPI_CHANNEL_TYPE_REPORT,
			MdsAPI_CFG_DEFAULT_KEY_RPT_ADDR, &_apiCfg.rptChannelCfg,
			&_apiCfg.subscribeInfo,
			_MdsClientApi_HandleReportMsg, _pSpi,
			_MdsClientApi_OnAsyncConnect, _pSpi,
			_MdsClientApi_OnAsyncDisconnect, _pSpi);
		if (__spk_unlikely(!pRptChannel)) {
			SLOG_ERROR("添加回报通道失败! channelTag[%s]",
				MdsAPI_CFG_DEFAULT_KEY_RPT_ADDR);
			MdsAsyncApi_ReleaseContext(pAsyncContext);
			return FALSE;
		}
	}

	_pAsyncContext = pAsyncContext;
	_pDefaultOrdChannel = pOrdChannel;
	_pDefaultRptChannel = pRptChannel;
	_isInitialized = TRUE;
	return TRUE;
}


/**
 * 设置客户端的IP和MAC
 *
 * @note    需要在 Start 前调用
 *
 * @param   pIpStr              点分十进制的IP地址字符串
 * @param   pMacStr             MAC地址字符串 (MAC地址格式 45:38:56:89:78:5A)
 * @retval  TRUE                成功
 * @retval  FALSE               失败
 */
BOOL
MdsClientApi::SetCustomizedIpAndMac(const char *pIpStr, const char *pMacStr) {
	return MdsApi_SetCustomizedIpAndMac(pIpStr, pMacStr);
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

	/* 启动异步API线程 (连接委托通道和回报通道) */
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
		SLOG_INFO("未配置委托通道或回报通道, 将仅连接查询通道, 无需启动异步API线程!");
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
 * 回报消息处理和会话管理回调函数
 * =================================================================== */

 /**
  * 连接或重新连接完成后的回调函数 (适用于基于异步API的委托通道和回报通道)
  *
  * <p> 回调函数说明:
  * - 对于回报通道, 需要通过该回调函数完成回报订阅操作。若函数指针为空, 则会使用通道配置中默认的
  *   回报订阅参数进行订阅。若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
  * - 若回调函数返回小于0的数, 则异步线程将中止运行
  * </p>
  *
  * <p> @note 关于上一次会话的最大请求数据编号 (针对委托通道)
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
  * <p> @note 关于最近接收到的回报数据编号 (针对回报通道):
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
	OesApiSubscribeInfoT    *pSubscribeInfo = (OesApiSubscribeInfoT *)NULL;
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

	if (pAsyncChannel->pChannelCfg->channelType == MDSAPI_CHANNEL_TYPE_REPORT) {
		/* 提取回报通道对应的订阅配置信息 */
		pSubscribeInfo = MdsAsyncApi_GetChannelSubscribeCfg(pAsyncChannel);
		if (__spk_unlikely(!pSubscribeInfo)) {
			SLOG_ERROR("Illegal extended subscribe info! " \
				"pAsyncChannel[%p], channelTag[%s]",
				pAsyncChannel, pAsyncChannel->pChannelCfg->channelTag);
			SLOG_ASSERT(0);

			SPK_SET_ERRNO(EINVAL);
			return SPK_NEG(EINVAL);
		}
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
	case MDSAPI_CHANNEL_TYPE_ORDER:
		SLOG_INFO("Order channel connected. server[%s:%d], " \
			"lastInMsgSeq[%" __SPK_FMT_LL__ "d], " \
			"lastOutMsgSeq[%" __SPK_FMT_LL__ "d]",
			pAsyncChannel->pSessionInfo->channel.remoteAddr,
			pAsyncChannel->pSessionInfo->channel.remotePort,
			pAsyncChannel->pSessionInfo->lastInMsgSeq,
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

	case MDSAPI_CHANNEL_TYPE_REPORT:
		/* 按照默认回报订阅参数从上次的断点位置开始订阅回报 */
		SLOG_INFO("Report channel connected, subscribe report data by " \
			"default. server[%s:%d], " \
			"lastInMsgSeq[%" __SPK_FMT_LL__ "d], " \
			"lastOutMsgSeq[%" __SPK_FMT_LL__ "d]",
			pAsyncChannel->pSessionInfo->channel.remoteAddr,
			pAsyncChannel->pSessionInfo->channel.remotePort,
			pAsyncChannel->pSessionInfo->lastInMsgSeq,
			pAsyncChannel->pSessionInfo->lastOutMsgSeq);

		pSubscribeInfo = MdsAsyncApi_GetChannelSubscribeCfg(pAsyncChannel);
		if (__spk_unlikely(!pSubscribeInfo)) {
			SLOG_ERROR("Illegal extended subscribe info! pAsyncChannel[%p]",
				pAsyncChannel);
			SLOG_ASSERT(0);

			SPK_SET_ERRNO(EINVAL);
			return SPK_NEG(EINVAL);
		}

		/*
		 * 关于 lastInMsgSeq 字段 (最近接收到的回报数据编号)
		 * @note 提示:
		 * - API会将回报数据的断点位置存储在 <code>pAsyncChannel->lastInMsgSeq</code> 和
		 *   <code>pSessionInfo->lastInMsgSeq</code> 字段中, 可以使用该值订阅回报
		 * - 对于SPI回调接口, 可以在OnConnect回调函数中重新设置
		 *   <code>pSessionInfo->lastInMsgSeq</code> 的取值来重新指定订阅条件
		 */
		if (__spk_unlikely(!MdsApi_SendReportSynchronization(
			pAsyncChannel->pSessionInfo, pSubscribeInfo->clEnvId,
			pSubscribeInfo->rptTypes,
			pAsyncChannel->pSessionInfo->lastInMsgSeq))) {
			SLOG_ERROR("Send report synchronization failure, will retry! " \
				"server[%s:%d]",
				pAsyncChannel->pSessionInfo->channel.remoteAddr,
				pAsyncChannel->pSessionInfo->channel.remotePort);

			/* 处理失败, 将重建连接并继续尝试执行 */
			return EAGAIN;
		}
		break;

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
 * 连接断开后的回调函数 (适用于基于异步API的委托通道和回报通道)
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
		== MDSAPI_CHANNEL_TYPE_ORDER ? "Order" : "Report",
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
		"lastInMsgSeq[%" __SPK_FMT_LL__ "d], " \
		"lastOutMsgSeq[%" __SPK_FMT_LL__ "d]",
		pSessionInfo->channel.remoteAddr, pSessionInfo->channel.remotePort,
		pSessionInfo->lastInMsgSeq, pSessionInfo->lastOutMsgSeq);

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


/**
 * 对接收到的回报消息进行处理的回调函数 (适用于回报通道)
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
 * @see     OesRptMsgT
 */
static int32
_MdsClientApi_HandleReportMsg(MdsApiSessionInfoT *pSessionInfo,
	SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
	MdsClientSpi            *pSpi = (MdsClientSpi *)pCallbackParams;
	OesRspMsgBodyT          *pRspMsg = (OesRspMsgBodyT *)pMsgBody;
	OesRptMsgT              *pRptMsg = &pRspMsg->rptMsg;

	SLOG_ASSERT(pSessionInfo && pMsgHead && pMsgBody);
	SLOG_ASSERT(pSpi);

	switch (pMsgHead->msgId) {
	case OESMSG_RPT_ORDER_INSERT:                           /* OES委托已生成 (已通过风控检查) @see OesOrdCnfmT */
		pSpi->OnOrderInsert(&pRptMsg->rptHead,
			&pRptMsg->rptBody.ordInsertRsp);
		break;

	case OESMSG_RPT_BUSINESS_REJECT:                        /* OES业务拒绝 (未通过风控检查等) @see OesOrdRejectT */
		pSpi->OnBusinessReject(&pRptMsg->rptHead,
			&pRptMsg->rptBody.ordRejectRsp);
		break;

	case OESMSG_RPT_ORDER_REPORT:                           /* 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知) @see OesOrdCnfmT */
		pSpi->OnOrderReport(&pRptMsg->rptHead,
			&pRptMsg->rptBody.ordCnfm);
		break;

	case OESMSG_RPT_TRADE_REPORT:                           /* 交易所成交回报 @see OesTrdCnfmT */
		pSpi->OnTradeReport(&pRptMsg->rptHead,
			&pRptMsg->rptBody.trdCnfm);
		break;

	case OESMSG_RPT_CASH_ASSET_VARIATION:                   /* 资金变动信息 @see OesCashAssetReportT */
		pSpi->OnCashAssetVariation(&pRptMsg->rptBody.cashAssetRpt);
		break;

	case OESMSG_RPT_STOCK_HOLDING_VARIATION:                /* 股票持仓变动信息 @see OesStkHoldingReportT */
		pSpi->OnStockHoldingVariation(&pRptMsg->rptBody.stkHoldingRpt);
		break;

	case OESMSG_RPT_OPTION_HOLDING_VARIATION:               /* 期权持仓变动信息 @see OesOptHoldingReportT */
		pSpi->OnOptionHoldingVariation(&pRptMsg->rptBody.optHoldingRpt);
		break;

	case OESMSG_RPT_OPTION_UNDERLYING_HOLDING_VARIATION:    /* 期权标的持仓变动信息 @see OesOptUnderlyingHoldingReportT */
		pSpi->OnOptionUnderlyingHoldingVariation(
			&pRptMsg->rptBody.optUnderlyingHoldingRpt);
		break;

	case OESMSG_RPT_OPTION_SETTLEMENT_CONFIRMED:            /* 期权账户结算单确认回报 @see OesOptSettlementConfirmReportT */
		pSpi->OnSettlementConfirmedRpt(&pRptMsg->rptHead,
			&pRptMsg->rptBody.optSettlementConfirmRpt);
		break;

	case OESMSG_RPT_FUND_TRSF_REJECT:                       /* 出入金委托响应-业务拒绝 @see OesFundTrsfRejectT */
		pSpi->OnFundTrsfReject(&pRptMsg->rptHead,
			&pRptMsg->rptBody.fundTrsfRejectRsp);
		break;

	case OESMSG_RPT_FUND_TRSF_REPORT:                       /* 出入金委托执行报告 @see OesFundTrsfReportT */
		pSpi->OnFundTrsfReport(&pRptMsg->rptHead,
			&pRptMsg->rptBody.fundTrsfCnfm);
		break;

	case OESMSG_RPT_MARKET_STATE:                           /* 市场状态信息 @see OesMarketStateInfoT */
		pSpi->OnMarketState(&pRspMsg->mktStateRpt);
		break;

	case OESMSG_RPT_NOTIFY_INFO:                            /* 通知消息 @see OesNotifyInfoReportT */
		pSpi->OnNotifyReport(&pRptMsg->rptBody.notifyInfoRpt);
		break;

	case OESMSG_SESS_HEARTBEAT:                             /* 心跳消息 */
		SLOG_DEBUG(">>> Recv heartbeat message.");
		break;

	case OESMSG_SESS_TEST_REQUEST:                          /* 测试请求消息 */
		SLOG_DEBUG(">>> Recv test-request response message.");
		break;

	case OESMSG_RPT_REPORT_SYNCHRONIZATION:                 /* 回报同步的应答消息 @see OesReportSynchronizationRspT */
		pSpi->OnReportSynchronizationRsp(&pRspMsg->reportSynchronizationRsp);
		break;

	default:
		/* 接收到非预期(未定义处理方式)的回报消息 */
		SLOG_ERROR("Invalid message type! msgId[0x%02X]",
			pMsgHead->msgId);
		break;
	}

	return 0;
}


/**
 * 对接收到的应答消息进行处理的回调函数 (适用于委托通道)
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
_MdsClientApi_HandleOrderChannelRsp(MdsApiSessionInfoT *pSessionInfo,
	SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
	OesRspMsgBodyT          *pRspMsg = (OesRspMsgBodyT *)pMsgBody;

	SLOG_ASSERT(pSessionInfo && pMsgHead && pMsgBody);

	switch (pMsgHead->msgId) {
	case OESMSG_SESS_HEARTBEAT:                 /* 心跳消息 */
		SLOG_DEBUG(">>> Recv heartbeat message.");
		break;

	case OESMSG_SESS_TEST_REQUEST:              /* 测试请求消息 */
		SLOG_DEBUG(">>> Recv test-request response message.");
		break;

	case OESMSG_NONTRD_CHANGE_PASSWORD:         /* 登录密码修改的应答消息 @see OesChangePasswordRspT */
		SLOG_DEBUG(">>> Recv change password response message. " \
			"username[%s], rejReason[%d]",
			pRspMsg->changePasswordRsp.username,
			pRspMsg->changePasswordRsp.rejReason);
		break;

	case OESMSG_NONTRD_OPT_CONFIRM_SETTLEMENT:  /* 结算单确认的应答消息 @see OesOptSettlementConfirmRspT */
		SLOG_DEBUG(">>> Recv option settlement confirm response message. " \
			"custId[%s], rejReason[%d]",
			pRspMsg->optSettlementConfirmRsp.custId,
			pRspMsg->optSettlementConfirmRsp.rejReason);
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


/**
 * 获取当前交易日
 *
 * @retval  >=0                 当前交易日 (格式：YYYYMMDD)
 * @retval  <0                  失败 (负的错误号)
 */
int32
MdsClientApi::GetTradingDay(void) {
	int32                   ret = 0;

	if (__spk_unlikely(!_isRunning || !_pSpi)) {
		SLOG_ERROR("Invalid params or running state! isRunning[%d], pSpi[%p]",
			_isRunning, _pSpi);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	ret = MdsApi_GetTradingDay(_pQryChannel);
	if (__spk_unlikely(ret < 0)) {
		SLOG_ERROR("获取当前交易日失败, 将断开并尝试重建查询通道! " \
			"ret[%d], error[%d - %s]",
			ret, MdsApi_GetLastError(),
			MdsApi_GetErrorMsg(MdsApi_GetLastError()));

		/* 查询失败, 断开并尝试重建查询通道 */
		_MdsClientApi_OnQueryDisconnect(_pQryChannel, _pSpi,
			&_apiCfg.qryChannelCfg);
	}

	return ret;
}


/**
 * 获取客户端总览信息
 *
 * @param[out]  pClientOverview 查询到的客户端总览信息
 * @retval  =0                  查询成功
 * @retval  <0                  失败 (负的错误号)
 */
int32
MdsClientApi::GetClientOverview(OesClientOverviewT *pClientOverview) {
	int32                   ret = 0;

	if (__spk_unlikely(!_isRunning || !_pSpi)) {
		SLOG_ERROR("Invalid params or running state! isRunning[%d], pSpi[%p]",
			_isRunning, _pSpi);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	ret = MdsApi_GetClientOverview(_pQryChannel, pClientOverview);
	if (__spk_unlikely(ret < 0)) {
		SLOG_ERROR("获取客户端总览信息失败, 将断开并尝试重建查询通道! " \
			"ret[%d], error[%d - %s]",
			ret, MdsApi_GetLastError(),
			MdsApi_GetErrorMsg(MdsApi_GetLastError()));

		/* 查询失败, 断开并尝试重建查询通道 */
		_MdsClientApi_OnQueryDisconnect(_pQryChannel, _pSpi,
			&_apiCfg.qryChannelCfg);
	}

	return ret;
}



/**
 * 查询通知消息回调包裹函数
 */
static __inline int32
_MdsClientApi_QueryNotifyInfo(MdsApiSessionInfoT *pSessionInfo,
	SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
	void *pCallbackParams) {
	((MdsClientSpi *)pCallbackParams)->OnQueryNotifyInfo(
		(OesNotifyInfoItemT *)pMsgBody, pQryCursor,
		((MdsClientSpi *)pCallbackParams)->currentRequestId);
	return 0;
}


/**
 * 查询通知消息
 *
 * @param   pQryFilter          查询条件过滤条件
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
MdsClientApi::QueryNotifyInfo(const OesQryNotifyInfoFilterT *pQryFilter,
	int32 requestId) {
	int32                   ret = 0;

	if (__spk_unlikely(!_isRunning || !_pSpi)) {
		SLOG_ERROR("Invalid params or running state! isRunning[%d], pSpi[%p]",
			_isRunning, _pSpi);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	_pSpi->currentRequestId = requestId;

	ret = MdsApi_QueryNotifyInfo(_pQryChannel, pQryFilter,
		_MdsClientApi_QueryNotifyInfo, (void *)_pSpi);
	if (__spk_unlikely(ret < 0)) {
		SLOG_ERROR("查询通知消息失败, 将断开并尝试重建查询通道! " \
			"ret[%d], error[%d - %s]",
			ret, MdsApi_GetLastError(),
			MdsApi_GetErrorMsg(MdsApi_GetLastError()));

		/* 查询失败, 断开并尝试重建查询通道 */
		_MdsClientApi_OnQueryDisconnect(_pQryChannel, _pSpi,
			&_apiCfg.qryChannelCfg);
	}

	return ret;
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
 * - 对于回报通道, 需要通过该回调函数完成回报订阅操作。若函数指针为空, 则会使用通道配置中默认的
 *   回报订阅参数进行订阅。若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * <p> @note 关于上一次会话的最大请求数据编号 (针对委托通道)
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
 * <p> @note 关于最近接收到的回报数据编号 (针对回报通道):
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
 * @param   pSubscribeInfo      默认的回报订阅参数 (仅适用于回报通道)
 * @retval  =0                  等于0, 成功 (不再执行默认的回调函数)
 * @retval  >0                  大于0, 忽略本次执行, 并继续执行默认的回调函数
 * @retval  <0                  小于0, 处理失败, 异步线程将中止运行
 */
int32
MdsClientSpi::OnConnected(eMdsApiChannelTypeT channelType,
	MdsApiSessionInfoT *pSessionInfo,
	OesApiSubscribeInfoT *pSubscribeInfo) {
	/*
	 * 返回值说明:
	 * - 返回大于0的值, 表示需要继续执行默认的 OnConnect 回调函数 (对于回报通道, 将使用配置
	 *   文件中的订阅参数订阅回报)
	 * - 若返回0, 表示已经处理成功 (包括回报通道的回报订阅操作也需要显式的调用并执行成功), 将
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
 * @param   pSubscribeInfo      默认的回报订阅参数 (仅适用于回报通道)
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
