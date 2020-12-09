# MDS-API Change Log    {#changelog}

MDS_0.16.1.1 / 2020-06-29
==============================================

  * 将系统下的时间戳全部升级为纳秒级时间戳, 以提高时延统计的精度
    - 时间戳字段的数据类型从 STimevalT/STimeval32T 变更为 STimespecT/STimespec32T
    - 协议保持兼容, 但如果使用到了时间戳字段下的微秒时间(tv_usec 字段), 则需要修改为纳秒时间(tv_nsec 字段), 否则会因为时间单位的调整而导致时延计算错误
  * 异步API新增如下接口
    - MdsAsyncApi_IsAllTerminated, 异步API检查所有线程是否均已安全退出
  * 同步API新增如下接口
    - 增加新的批量查询期权静态信息列表接口, 以支持同时指定和查询多个期权合约代码
      - MdsApi_QueryOptionStaticInfoList, 批量查询期权静态信息列表
      - MdsApi_QueryOptionStaticInfoList2, 批量查询期权静态信息列表 (字符串指针数组形式的证券代码列表)
    - 增加新的批量查询证券(股票/债券/基金)静态信息列表接口, 以支持同时指定和查询多个证券代码
      - MdsApi_QueryStockStaticInfoList, 批量查询证券(股票/债券/基金)静态信息列表
      - MdsApi_QueryStockStaticInfoList2, 批量查询证券(股票/债券/基金)静态信息列表 (字符串指针数组形式的证券代码列表)
    - MdsApi_GetChannelGroupLastRecvTime, 返回通道组最近接收消息时间
    - MdsApi_GetChannelGroupLastSendTime, 返回通道组最近发送消息时间
    - MdsApi_HasStockStatus, 返回现货产品是否具有指定状态
    - __MdsApi_CheckApiVersion, 检查API版本是否匹配 (检查API头文件和库文件的版本是否匹配)
  * 为支持创业板注册制改革, 证券静态信息 (MdsStockStaticInfoT) 中新增如下字段:
    - 是否注册制 (isRegistration)
    - 币种 (currType)
    - 投资者适当性管理分类 (qualificationClass)
    - 证券状态 (securityStatus)
    - 证券属性 (securityAttribute), 保留字段
    - 连续停牌标识 (suspFlag)
    - 是否支持当日回转交易 (isDayTrading)
    - 是否为融资标的 (isCrdMarginTradeUnderlying)
    - 是否为融券标的 (isCrdShortSellUnderlying)
    - 是否为融资融券担保品 (isCrdCollateral)
    - 是否尚未盈利 (isNoProfit)
    - 是否存在投票权差异 (isWeightedVotingRights)
    - 是否具有协议控制框架 (isVie)
    - 限价买入单位 (lmtBuyQtyUnit)
    - 限价卖出单位 (lmtSellQtyUnit)
    - 市价买入单位 (mktBuyQtyUnit)
    - 市价卖出单位 (mktSellQtyUnit)
    - 连续竞价范围限制类型 (auctionLimitType)
    - 连续竞价范围基准价类型 (auctionReferPriceType)
    - 连续竞价范围涨跌幅度 (auctionUpDownRange)
    - 面值 (parValue), 兼容旧版'parPrice'字段
    - 上市日期 (listDate)
    - 到期日期 (maturityDate)
    - 基础证券代码 (underlyingSecurityId)
    - 证券长名称 (securityLongName)
    - 证券英文名称 (securityEnglishName)
    - ISIN代码 (securityIsinCode)
  * 证券静态信息 (MdsStockStaticInfoT) 中新增证券子类型(同OES):
    - 创业板存托凭证 (OES_SUB_SECURITY_TYPE_STOCK_GEMCDR)
    - 可交换债券 (OES_SUB_SECURITY_TYPE_BOND_EXG)
    - 商品期货ETF (OES_SUB_SECURITY_TYPE_ETF_COMMODITY_FUTURES)
  * 优化异步API
    - 为异步API增加是否优先使用大页内存来创建异步队列的配置项
    - 为异步API的I/O线程增加追加模式输出的配置项
    - 为异步API的I/O线程增加支持忙等待的配置选项，以使异步队列的延迟统计结果更接近实际情况
    - 删除并不适用于行情异步API的密码修改接口 MdsAsyncApi_SendChangePasswordReq
  * API中添加vs2015工程样例

MDS_0.16.0.5 / 2020-04-17
==============================================

  * 更新'昨日收盘价'等字段的注释信息
  * Merge MDS_0.15.10.5
    - 为异步API增加对UDP行情数据的本地订阅/过滤功能
    - 统一沪深期权行情的昨收盘价字段, 不再通过该字段推送昨结算价（深圳期权快照中没有结算价字段）
    - 调整组播行情的行为, 不再强制过滤掉重复的快照行情和重建到的逐笔行情, 并允许通过订阅条件进行控制
    - 调整发布API示例代码的目录位置

MDS_0.16.0.4 / 2020-02-28
==============================================

  * Merge OES_0.15.10.3
    - refactor: 重构和完善异步API (提供统一且完备的异步API接口)

MDS_0.16.0.3 / 2020-01-17
==============================================

  * Merge OES_0.15.10.1
    - 重构异步API接口, 统一交易和行情的异步API定义 (接口发生了变化, 不兼容之前版本的异步API)

MDS_0.16.0.2 (内部测试) / 2020-01-03
==============================================

  * Merge OES_0.15.10 (未发布)
    - 重构异步API接口, 统一交易和行情的异步API定义 (接口发生了变化, 不兼容之前版本的异步API)

MDS_0.16.0.1 / 2019-12-12
==============================================

  * 完善异步API的实现机制及其异常处理

MDS_0.16 / 2019-11-20
==============================================

  * 增加查询期权静态信息的接口
    - MdsApi_QueryOptionStaticInfo

MDS_0.15.11.3 / 2020-06-29
==============================================

  * 将系统下的时间戳全部升级为纳秒级时间戳, 以提高时延统计的精度
    - 时间戳字段的数据类型从 STimevalT/STimeval32T 变更为 STimespecT/STimespec32T
    - 协议保持兼容, 但如果使用到了时间戳字段下的微秒时间(tv_usec 字段), 则需要修改为纳秒时间(tv_nsec 字段), 否则会因为时间单位的调整而导致时延计算错误
  * 增加新的批量查询证券(股票/债券/基金)静态信息列表接口, 以支持同时指定和查询多个证券代码
    - MdsApi_QueryStockStaticInfoList, 批量查询证券(股票/债券/基金)静态信息列表
    - MdsApi_QueryStockStaticInfoList2, 批量查询证券(股票/债券/基金)静态信息列表 (字符串指针数组形式的证券代码列表)
  * 增加用于校验API版本号是否匹配的辅助函数
    - __MdsApi_CheckApiVersion

MDS_0.15.11.1 / 2020-06-08
==============================================

  * 异步API新增如下接口
    - MdsAsyncApi_IsAllTerminated, 异步API检查所有线程是否均已安全退出
  * 同步API新增如下接口
    - MdsApi_GetChannelGroupLastRecvTime, 返回通道组最近接收消息时间
    - MdsApi_GetChannelGroupLastSendTime, 返回通道组最近发送消息时间
    - MdsApi_HasStockStatus, 辅助判断现货产品状态
  * 为支持创业板注册制改革, 证券静态信息 (MdsStockStaticInfoT) 中新增如下字段:
    - 是否注册制 (isRegistration)
    - 币种 (currType)
    - 投资者适当性管理分类 (qualificationClass)
    - 证券状态 (securityStatus)
    - 证券属性 (securityAttribute), 保留字段
    - 连续停牌标识 (suspFlag)
    - 是否支持当日回转交易 (isDayTrading)
    - 是否为融资标的 (isCrdMarginTradeUnderlying)
    - 是否为融券标的 (isCrdShortSellUnderlying)
    - 是否为融资融券担保品 (isCrdCollateral)
    - 是否尚未盈利 (isNoProfit)
    - 是否存在投票权差异 (isWeightedVotingRights)
    - 是否具有协议控制框架 (isVie)
    - 限价买入单位 (lmtBuyQtyUnit)
    - 限价卖出单位 (lmtSellQtyUnit)
    - 市价买入单位 (mktBuyQtyUnit)
    - 市价卖出单位 (mktSellQtyUnit)
    - 连续竞价范围限制类型 (auctionLimitType)
    - 连续竞价范围基准价类型 (auctionReferPriceType)
    - 连续竞价范围涨跌幅度 (auctionUpDownRange)
    - 面值 (parValue), 兼容旧版'parPrice'字段
    - 上市日期 (listDate)
    - 到期日期 (maturityDate)
    - 基础证券代码 (underlyingSecurityId)
    - 证券长名称 (securityLongName)
    - 证券英文名称 (securityEnglishName)
    - ISIN代码 (securityIsinCode)
  * 证券静态信息 (MdsStockStaticInfoT) 中新增证券子类型(同OES):
    - 创业板存托凭证 (OES_SUB_SECURITY_TYPE_STOCK_GEMCDR)
    - 可交换债券 (OES_SUB_SECURITY_TYPE_BOND_EXG)
    - 商品期货ETF (OES_SUB_SECURITY_TYPE_ETF_COMMODITY_FUTURES)
  * 优化异步API
    - 为异步API增加是否优先使用大页内存来创建异步队列的配置项
    - 为异步API的I/O线程增加追加模式输出的配置项
    - 为异步API的I/O线程增加支持忙等待的配置选项，以使异步队列的延迟统计结果更接近实际情况
    - 删除并不适用于行情异步API的密码修改接口 MdsAsyncApi_SendChangePasswordReq
  * API中添加vs2015工程样例

MDS_0.15.10.5 / 2020-04-07
==============================================

  * 为异步API增加对UDP行情数据的本地订阅/过滤功能
  * 统一沪深期权行情的昨收盘价字段，不再通过该字段推送昨结算价（深圳期权快照中没有结算价字段）
  * 调整组播行情的行为, 不再强制过滤掉重复的快照行情和重建到的逐笔行情，并允许通过订阅条件进行控制
  * 调整发布API示例代码的目录位置

MDS_0.15.10.3 / 2020-02-28
==============================================

  * refactor: 重构和完善异步API (提供统一且完备的异步API接口)

MDS_0.15.10.1 / 2020-01-17
==============================================

  * fix: 初始化网络环境时自动屏蔽SIGPIPE信号，以避免连接断开以后重复send导致程序异常退出
  * 重构异步API接口, 统一交易和行情的异步API定义 (接口发生了变化, 不兼容之前版本的异步API)

MDS_0.15.9.4 / 2019-12-24
==============================================

  * 增加对深交所国证指数快照行情的支持
  * 证券静态信息结构体中增加字段 '总股本(outstandingShare)' 和 '流通股数量(publicFloatShare)' (协议保持兼容)
  * 调整行情组播频道的划分, 划分为两个独立的沪/深快照频道和两个独立的沪/深逐笔频道, 共4个组播频道 (API及配置文件保持兼容, 但频道内容发生了变化)
    - 快照-频道1 (Snap1): 上海L1/L2快照
    - 快照-频道2 (Snap2): 深圳L1/L2快照
    - 逐笔-频道1 (Tick1): 上海逐笔成交
    - 逐笔-频道2 (Tick2): 深圳逐笔成交/逐笔委托

MDS_0.15.9.1 / 2019-08-16
==============================================

  * 增加异步API接口, 以支持行情异步接收和处理
  * 增加对重建到的逐笔数据的订阅和推送处理 (行情订阅条件和订阅配置中增加 '逐笔数据的数据重建标识 tickRebuildFlag', 用于标识是否订阅重建到的逐笔数据)
  * 增加批量订阅模式, 以支持更灵活可控的行情订阅
  * 完善对行情订阅条件中起始时间和初始行情标志的支持, 允许在会话过程中的任意时间指定 beginTime 和 isRequireInitialMktData 订阅参数
  * 增加为SubscribeByString设置附加订阅参数的API接口
    - MdsApi_SetThreadSubscribeTickType
    - MdsApi_SetThreadSubscribeTickRebuildFlag
    - MdsApi_SetThreadSubscribeTickExpireType
    - MdsApi_SetThreadSubscribeRequireInitMd
    - MdsApi_SetThreadSubscribeBeginTime
  * 增加设置登录以后是否自动执行行情订阅操作的接口，以允许禁用登录后的自动行情订阅
    - MdsApi_SetThreadAutoSubscribeOnLogon
  * 增加用于解析CVS格式行情数据文件的辅助API接口
    - MdsCsvParser_DecodeCsvRecord
  * 优化行情订阅接口, 取消基础订阅接口一次最大只能订阅4000只证券代码的限制
    - MdsApi_SubscribeMarketData
  * 重命名样例代码文件, 并整理注释信息
  * 新增错误码
    - 1037, 集群编号不匹配
    - 1038, 无此操作权限
  * 替换头文件中使用的 likely/unlikely 关键字, 以避免与第三方库的同名函数冲突
    - 若编译时提示 likely 与 boost 库中的函数名称冲突, 可以通过指定宏 __NO_SHORT_LIKELY 来解决

MDS_0.15.9 / 2019-05-31
==============================================

  * fix: 修复API无法支持取值大于1024的文件描述符的问题 (因为select的限制, 当文件描述符的取值大于1024时, 会导致堆栈溢出)
  * fix: 扩大深圳证券业务开关的最大数量（该修改会对之前版本API的延迟统计造成影响）, 以应对行情数据内容的更新
  * 调整行情数据类型(mdStreamType, eMdsMdStreamTypeT)的取值, 使其可以标识出快照行情的具体数据类型
     - 该修改会存在兼容性问题, 客户端程序可以通过编译错误来识别需要调整的地方 (如果没有编译错误就不需要调整)
     - 行情数据类型的取值将尽量与消息类型保持一致, 但以下类型比较特殊：
       - 深圳成交量统计指标
       - 上交所 Level1 行情快照-债券
       - 上交所 Level1 行情快照-基金
  * 重命名 securityType => mdProductType, 以避免与交易端的证券类型混淆
    - securityType => mdProductType
    - eMdsSecurityTypeT => eMdsMdProductTypeT
  * 删除已经废弃的虚拟集合竞价消息的消息定义和数据类型定义
  * 调整快照头 MdsMktDataSnapshotHeadT 中的内部字段定义, 将 __origTickSeq 字段拆分为 __origTickSeq + __lastUpdateTime 两个字段 (内部使用的字段, 协议保持兼容)
  * 增加修改客户端登录密码接口
    - MdsApi_SendChangePasswordReq
  * 增加设置/获取客户端自定义的本地IP/MAC地址的接口
    - MdsApi_SetCustomizedIp
    - MdsApi_GetCustomizedIp
    - MdsApi_SetCustomizedMac
    - MdsApi_GetCustomizedMac
  * 增加设置/获取客户端自定义的设备序列号的接口
    - MdsApi_SetCustomizedDriverId
    - MdsApi_GetCustomizedDriverId
  * 新增错误码
    - 1029, 密码未改变
    - 1034, 密码强度不足
    - 1036, 未通过黑白名单检查

MDS_0.15.8 / 2019-02-22
==============================================

  * fix: 修复API无法支持取值大于1024的文件描述符的问题 (因为select的限制, 当文件描述符的取值大于1024时, 会导致堆栈溢出)
  * 重命名 securityType => mdProductType, 以避免与交易端的证券类型混淆
    - securityType => mdProductType
    - eMdsSecurityTypeT => eMdsMdProductTypeT
  * 删除已经废弃的虚拟集合竞价消息的消息定义和数据类型定义
  * 调整快照头 MdsMktDataSnapshotHeadT 中的内部字段定义, 将 __origTickSeq 字段拆分为 __origTickSeq + __lastUpdateTime 两个字段 (内部使用的字段, 协议保持兼容)
  * 增大登录时的网络超时时间, 避免因为系统繁忙等原因导致登录失败
  * 调整错误描述
    - 1007, 非服务开放时间
    - 1022, 尚不支持或尚未开通此业务
    - 1035, 非法的产品类型

MDS_0.15.7.6 / 2018-11-28
==============================================

  * 添加批量查询行情快照接口
    - MdsApi_QuerySnapshotList
  * 按照配置信息结构体, 增加初始化客户端环境接口
    - MdsApi_InitAllByCfgStruct

MDS_0.15.7.6 / 2018-11-03
==============================================

  * 增加查询证券(股票/债券/基金)静态信息的接口
    - MdsApi_QueryStockStaticInfo
  * 新增错误码定义
    - 1035, 非法的产品类型（MDSERR_ILLEGAL_PRODUCT_TYPE）

MDS_0.15.7.5 / 2018-08-31
==============================================

  * 修复 '返回错误号对应的错误信息 (MdsApi_GetErrorMsg)' 接口, windows平台获取错误信息不准确的问题

MDS_0.15.7.4 / 2018-08-31
==============================================

  * 增加设置当前线程登录用户名/登录密码的接口
    - MdsApi_SetThreadUsername
    - MdsApi_SetThreadPassword
  * 增加返回当前线程最近一次API调用失败的错误号的接口
    - OesApi_GetLastError
    - OesApi_SetLastError
  * 新增错误号详见 mds_errors.h
  * Merge MDS_0.15.5.16
    - fix: 修复当多个线程同时初始化API日志时, 会导致日志信息重复输出的问题
    - 增加 MdsApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
    - 重构 SubscribeByString 接口
      - 支持订阅所有产品的行情或不订阅任何产品的行情
      - 支持通过 .SH 或 .SZ 后缀为证券代码指定其所属的交易所
      - 添加 MdsHelper_SetTickTypeOnSubscribeByString 接口, 以设置SubscribeByString默认使用的数据模式 (TickType)
      - 增量订阅时, 允许不指定 dataType (小于0) 而继承之前订阅的数据类型
    - 增加可订阅的数据种类 (DataType), 以支持单独订阅指数行情和期权行情
      - MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT, 与L1_SNAPSHOT的区别在于, INDEX_SNAPSHOT可以单独订阅指数行情
      - MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT, 与L1_SNAPSHOT的区别在于, OPTION_SNAPSHOT可以单独订阅期权行情
    - 增加可以处理压缩过的消息的 WaitOnMsg 接口:
      - MdsApi_WaitOnMsgCompressible
      - MdsApi_WaitOnTcpChannelGroupCompressible
      - 与不带 Compressible 后缀的接口相比, 带 Compressible 后缀的接口会自动检测和处理压缩过的消息, 但也会因此带来微小的性能损失

MDS_0.15.5.16 / 2018-08-31
==============================================

  * fix: 修复当多个线程同时初始化API日志时, 会导致日志信息重复输出的问题
  * 增加 MdsApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
  * 增加设置当前线程登录用户名/登录密码的接口
    - MdsApi_SetThreadUsername
    - MdsApi_SetThreadPassword
  * 增加返回最近一次API调用失败的错误号的接口
    - MdsApi_GetLastError
  * 重构 SubscribeByString 接口
    - 支持订阅所有产品的行情或不订阅任何产品的行情
    - 支持通过 .SH 或 .SZ 后缀为证券代码指定其所属的交易所
    - 添加 MdsHelper_SetTickTypeOnSubscribeByString 接口, 以设置SubscribeByString默认使用的数据模式 (TickType)
    - 增量订阅时, 允许不指定 dataType (小于0) 而继承之前订阅的数据类型
  * 增加可订阅的数据种类 (DataType), 以支持单独订阅指数行情和期权行情
    - MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT, 与L1_SNAPSHOT的区别在于, INDEX_SNAPSHOT可以单独订阅指数行情
    - MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT, 与L1_SNAPSHOT的区别在于, OPTION_SNAPSHOT可以单独订阅期权行情
  * 增加可以处理压缩过的消息的 WaitOnMsg 接口:
    - MdsApi_WaitOnMsgCompressible
    - MdsApi_WaitOnTcpChannelGroupCompressible
    - 与不带 Compressible 后缀的接口相比, 带 Compressible 后缀的接口会自动检测和处理压缩过的消息, 但也会因此带来微小的性能损失

MDS_0.15.5.11 / 2018-06-05
==============================================

  * fix: 扩大Level2增量更新消息支持的最大价位变更数量和委托明细数量, 修复在巨幅波动场景下会因为支持的价位数量不足导致丢失价位信息的BUG
    - 如果使用的是旧版本的API, 那么服务器端将不再推送增量更新消息 (只推送全量快照), 以此来保持兼容
    - 如果需要使用增量更新消息的话, 就需要更新到最新版本的API, 否则不需要更新API

MDS_0.15.5.10 / 2018-05-24
==============================================

  * 行情订阅条件和订阅配置中增加 '逐笔数据的过期时间类型 tickExpireType' (兼容之前版本)
  * 增加了一个仅内部使用的行情订阅条件 '待订阅的内部频道号', 前端不需要关心和处理 (兼容之前版本)

MDS_0.15.5.4 / 2018-02-22
==============================================

  * 调整接口 MdsApi_InitAll, 增加一个函数参数 (pUdpTickOrderAddrKey), 以支持分别订阅逐笔成交和逐笔委托的行情组播
  * Merge MDS_0.15.5.2
    - fix: 解决在Windows下的兼容性问题
    - 增加接口 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime, 用于获取通道最近接受/发送消息的时间
    - 登录失败时, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因

MDS_0.15.5.2 / 2018-01-29 (解决Windows兼容性问题的API更新版本)
==============================================

  * fix: 解决在Windows下的兼容性问题。包括:
    - fix: 在Windows下, API的Socket非阻塞模式有问题, 只能工作在阻塞模式下
    - fix: 在Windows下, 当没有行情数据时, 行情订阅的发送处理会长时间夯住, 直到有心跳消息触发才返回
    - fix: 在Windows下, 当在调试模式下运行时, 如果网络连接异常的话, 在退出时(关闭socket连接时)就会报异常
    - fix: 在Windows下, 不能自动获取IP和MAC地址, 需要显式的设置客户端本地的IP和MAC
  * 增加接口 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime, 用于获取通道最近接受/发送消息的时间
  * 登录失败时, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因

MDS_0.15.5.1 / 2017-11-22
==============================================

  * fix: 修复 MdsApi_InitAllByConvention() 接口总是返回连接失败的BUG
  * 增加数值类型的协议版本号 MDS_APPL_VER_VALUE, 以方便比对版本
  * 增加 MdsApi_IsValidTcpChannel、MdsApi_IsValidUdpChannel 等接口, 用于判断通道是否已经连接且有效

MDS_0.15.5 / 2017-11-12
==============================================

  * 新增接口 '获取API的发行版本号 (MdsApi_GetApiVersion)'
  * 默认开启用于统计延时的打点信息, 并将打点信息的时间戳类型改为 timeval32 (STimeval32T) 类型
  * 服务器端删除了对JSON等通信协议等支持, 改为只支持二进制协议
  * 在行情组播中推送逐笔数据, 并划分行情组播信道分别推送L1快照、L2快照和逐笔数据
  * 调整接口 MdsApi_InitAll, 以支持同时初始化多个组播通道
  * 增加通道组相关的 API 接口, 以支持同时接收多个连接通道的数据

MDS_0.15.3.3 / 2017/08/20
==============================================

 * 新增接口 '重置线程级别的日志记录器名称 (MdsApi_ResetThreadLoggerName)', 以支持为当前线程设置独立的日志文件

MDS_0.15.3 / 2017-08-14
==============================================

  * Merge MDS_0.12.9.12
    - fix: 针对Windows平台, 因为GNULib的recv方法在多线程时有问题, 会出现不同的 Socket 互相干扰和串行执行的现象, 所以暂时切换回使用只能工作于阻塞模式的read/write方法
    - 已知问题:
      - 在Windows下, API的Socket非阻塞模式有问题, 暂时只能工作在阻塞模式下
  * Merge MDS_0.12.9.11
    - fix: 重构跨平台处理, 完善API对Windows平台的支持
      - fix: 修复在Windows下，Socket未能正确设置为非阻塞模式的BUG
      - fix: 修复在Windows下，因为errno不兼容导致网络处理失败的BUG
      - fix: 修复在Windows下，因为文件路径处理方式不兼容，导致日志初始化失败的BUG
      - fix: 修复在Windows下，个别函数不兼容导致编译警告和运行错误的问题
      - fix: 修复因为中文字符编码不一致导致在Windows下编译失败的问题
      - refactor: 在API头文件中默认引用 spk_platforms.h 头文件
      - refactor: 重构API样例代码和样例配置文件

MDS_0.15.2 / 2017-07-12
==============================================

  * API 与 0.12.9.7 版本相同
    - 不再对外发布逐笔丢失消息(MDS_MSGTYPE_L2_TICK_LOST), 该消息已废弃

MDS_0.15.1 / 2017-06-26
==============================================

  * fix: 修正性能测试版本的编译错误
  * API 与 0.12.8 版本相同，无变化

MDS_0.12.9.12 / 2017-08-13
==============================================

  * fix: 针对Windows平台, 因为GNULib的recv方法在多线程时有问题, 会出现不同的 Socket 互相干扰和串行执行的现象, 所以暂时切换回使用只能工作于阻塞模式的read/write方法
  * 已知问题:
    - 在Windows下, API的Socket非阻塞模式有问题, 暂时只能工作在阻塞模式下

MDS_0.12.9.11 / 2017-08-12
==============================================

  * 重构跨平台处理, 完善API对Windows平台的支持
    - fix: 修复在Windows下，Socket未能正确设置为非阻塞模式的BUG
    - fix: 修复在Windows下，因为errno不兼容导致网络处理失败的BUG
    - fix: 修复在Windows下，因为文件路径处理方式不兼容，导致日志初始化失败的BUG
    - fix: 修复在Windows下，个别函数不兼容导致编译警告和运行错误的问题
    - fix: 修复因为中文字符编码不一致导致在Windows下编译失败的问题
    - refactor: 重构跨平台处理, 完善对Windows平台的支持, 并在API头文件中默认引用spk_platforms.h
    - refactor: 微调API样例代码和样例配置文件

MDS_0.12.9.7 / 2017-07-12
==============================================

  * 不再对外发布逐笔丢失消息(MDS_MSGTYPE_L2_TICK_LOST), 该消息已废弃

MDS_0.12.9_RC1 / 2017-06-05
==============================================

  * API 与 0.12.8 版本相同，无变化

MDS_0.12.8.1 / 2017-04-24 (API升级指引)
==============================================

### 消息代码的变更
    1. 重新定义消息类型的取值
    2. 将Level1证券行情全幅消息拆分为'Level1市场行情快照'、'指数行情快照'、'期权行情快照'三个消息:
        - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH (Level1 市场行情快照)
        - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH       (指数行情快照)
        - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH      (期权行情快照)
    3. 新增Level2行情消息:
        - MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT           (Level2 市场行情快照)
        - MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT           (Level2 委托队列快照 (买一/卖一前五十笔委托数量))
        - MDS_MSGTYPE_L2_TRADE                          (逐笔成交)
        - MDS_MSGTYPE_L2_ORDER                          (逐笔委托 (仅深圳))
        - MDS_MSGTYPE_L2_MARKET_OVERVIEW                (市场总览消息 (仅上海))
        - MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE          (虚拟集合竞价消息 (仅上海))
        - MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL        (增量更新消息, 仅在 TickType 为 AllIncrements 时存在 (仅上海))
        - MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL        (增量更新消息, 仅在 TickType 为 AllIncrements 时存在 (仅上海))
    4. 新增通知消息:
        - MDS_MSGTYPE_L2_TICK_LOST                      (逐笔数据丢失, 逐笔成交/逐笔委托发生了数据丢失, 并且无法重建, 将放弃这些丢失的逐笔数据)

### 结构体的变更
    1. 删除的结构体和字段
        - 删除独立的 MdsMktDataSnapshotEntryMetaT 结构体,
          将字段整合到 MdsMktDataSnapshotHeadT 中, 并删除原 meta.priceUnit (价格单位) 字段
        - 删除 MdsStockSnapshotBodyT.MDStreamID, MdsIndexSnapshotBodyT.MDStreamID 字段
    2. 重命名的结构体和字段
        - 重命名 MdsMktDataSnapshotEntryT -> MdsL1SnapshotBodyT
        - 重命名 MdsIndexDataSnapshotEntryT -> MdsIndexSnapshotBodyT
        - 重命名 MdsStockDataSnapshotEntryT -> MdsStockSnapshotBodyT
        - 重命名 MdsStockSnapshotBodyT.PreCloseIOPV -> NAV
        - 重命名并拆分原五档价位字段 MdsStockSnapshotBodyT.PriceLevel[5] -> BidLevels[5] + OfferLevels[5]
            - 可以参考如下正则表达式进行替换:
            - ``PriceLevel\[(\w+)\].BuyPrice -> BidLevels[\1].Price``
            - ``PriceLevel\[(\w+)\].BuyVolume -> BidLevels[\1].OrderQty``
            - ``PriceLevel\[(\w+)\].SellPrice -> OfferLevels[\1].Price``
            - ``PriceLevel\[(\w+)\].SellVolume -> OfferLevels[\1].OrderQty``
        - 重命名原快照行情中的成交总量字段 TradeVolume -> TotalVolumeTraded
    3. 新增的结构体和字段
        - 为'市场状态'、'证券实时状态'和'市场总览消息'消息添加 __exchSendingTime 和 __mdsRecvTime 字段，以方便比对实际的行情延时
        - 扩展'证券行情全幅消息(MdsMktDataSnapshotT)'的定义, 添加Level2快照消息体, 完整消息体定义如下:
            - MdsL2StockSnapshotBodyT             l2Stock;                  (Level2 快照行情(股票、债券、基金))
            - MdsL2StockSnapshotIncrementalT      l2StockIncremental;       (Level2 快照行情的增量更新消息)
            - MdsL2BestOrdersSnapshotBodyT        l2BestOrders;             (Level2 买一／卖一前五十笔委托明细)
            - MdsL2BestOrdersSnapshotIncrementalT l2BestOrdersIncremental;  (Level2 买一／卖一前五十笔委托明细的增量更新消息)
            - MdsStockSnapshotBodyT               stock;                    (Level1 股票、债券、基金行情数据)
            - MdsStockSnapshotBodyT               option;                   (Level1/Level2 期权行情数据)
            - MdsIndexSnapshotBodyT               index;                    (Level1/Level2 指数行情数据)
            - MdsL2VirtualAuctionPriceT           l2VirtualAuctionPrice;    (Level2 虚拟集合竞价 (仅上证))
            - MdsL2MarketOverviewT                l2MarketOverview;         (Level2 市场总览 (仅上证))
        - 新增逐笔行情结构体定义:
            - MdsL2TradeT                               (逐笔成交)
            - MdsL2OrderT                               (逐笔委托)

### 行情订阅相关的变更
    1. 重新定义了行情订阅消息, 包括如下字段和参数:
        - 订阅模式 (subMode) @see eMdsSubscribedTickTypeT
            - 0: (Set) 重新订阅，设置为订阅列表中的股票
            - 1: (Append) 追加订阅，增加订阅列表中的股票
            - 2: (Delete) 删除订阅，删除订阅列表中的股票
        - 数据模式, 订阅最新的行情快照还是所有时点的数据 (tickType) @see eMdsSubscribedTickTypeT
            - 0: (LatestSimplified) 只订阅最新的行情快照数据, 并忽略和跳过已经过时的数据 (推荐使用该模式即可)
        - 指定市场和证券类型的订阅标志
            - 包括如下字段:
                - sseStockFlag/sseIndexFlag/sseOptionFlag
                - szseStockFlag/szseIndexFlag/szseOptionFlag
            - 取值说明 @see eMdsMktSubscribeFlagT
                - 0: (Default) 根据订阅列表订阅产品行情
                - 1: (All) 订阅该市场和证券类型下所有产品的行情
                - 2: (Disable) 禁用该市场下所有产品的行情
        - 在推送实时行情数据之前, 是否需要推送已订阅产品的初始的行情快照 (isRequireInitialMktData)
            - 0: 不需要
            - 1: 需要, 即确保客户端可以至少收到一幅已订阅产品的快照行情 (如果有的话)
        - 订阅的数据种类 (dataTypes) @see eMdsSubscribeDataTypeT
            - 0:      默认数据种类 (所有)
            - 0x0001: L1快照/指数/期权
            - 0x0002: L2快照
            - 0x0004: L2委托队列
            - 0x0008: L2逐笔成交
            - 0x0010: L2逐笔委托（深圳）
            - 0x0020: L2虚拟集合竞价（上海）
            - 0x0040: L2市场总览（上海）
            - 0x0100: 市场状态（上海）
            - 0x0200: 证券实时状态（深圳）
            - 0xFFFF: 所有数据
            - 例如, 如果只需要订阅 'L1快照' 和 'L2快照', 则可以将 dataTypes 设置为:
                - 0x01 | 0x02
        - 请求订阅的行情数据的起始时间 (beginTime)
            - 小于 0: 从头开始获取
            - 等于 0: 从最新位置开始获取实时行情
            - 等于 0: 从指定的起始时间开始获取 (格式为: HHMMSS 或 HHMMSSsss)
        - 为了方便使用, 扩大每个订阅请求中能同时指定的产品数量至: 4000
    2. 调整了行情订阅的应答消息
        - 将返回各市场的实际订阅结果, 即实际已订阅的产品数量
    3. 重命名原行情订阅接口
        - 重命名 MdsApi_SubscribeMarketData -> MdsApi_SyncSubscribeOnLogon
          发送证券行情订阅消息，并同步等待应答消息的返回 (仅适用于连接建立后的初次订阅)
        - 重命名 MdsApi_ResubscribeMarketData -> MdsApi_SubscribeMarketData
          以异步的方式发送证券行情实时订阅请求，以重新订阅、追加订阅或删除订阅行情数据
    4. 增加了几个更便于使用的行情订阅接口
        - MdsApi_SubscribeByString                      (直接根据字符串形式的证券代码列表订阅行情信息)
        - MdsApi_SubscribeByString2                     (以字符串指针数组形式的证券代码列表订阅行情信息)
        - MdsApi_SubscribeByStringAndPrefixes           (直接根据字符串形式的证券代码列表和证券代码前缀列表订阅行情信息)
        - MdsApi_SubscribeByStringAndPrefixes2          (以字符串指针数组形式的证券代码列表以及证券代码前缀列表订阅行情信息)
        - 这几个字符串形式的订阅接口, 没有产品数量限制, 可以一次行传入所有待订阅的产品代码列表
        - 为了简化使用, 建议直接使用基于字符串形式的订阅接口即可, 但如果需要进行更细粒度的控制,
          则还需要通过 MdsApi_SubscribeMarketData 接口进行订阅
        - 订阅接口的使用示例, 可以参考样例代码:
            - mds_subscribe_sample.c 样例文件中的函数 MdsApiSample_ResubscribeByCodeFile
    5. 增加了几个辅助的(二进制)订阅请求信息维护函数
        - MdsHelper_ClearSubscribeRequestEntries        (清空订阅信息中的产品列表)
        - MdsHelper_SetSubscribeRequestMode             (设置订阅模式)
        - MdsHelper_SetSubscribeRequestTickType         (设置数据模式 (TickType))
        - MdsHelper_SetSubscribeRequestDataTypes        (设置订阅的数据种类)
        - MdsHelper_SetSubscribeRequestSubFlag          (设置指定市场和证券类型的订阅标志)
        - MdsHelper_AddSubscribeRequestEntry            (添加待订阅产品到订阅信息中)

### 行情处理相关的变更
    1. 更新行情订阅配置, 设置需要订阅的数据种类
    2. 更新行情处理方法, 处理以下这些新增的行情消息 (如果已经订阅了的话):
        - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH (Level1 市场行情快照)
        - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH       (指数行情快照)
        - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH      (期权行情快照)
        - MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT           (Level2 市场行情快照)
        - MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT           (Level2 委托队列快照 (买一/卖一前五十笔委托数量))
        - MDS_MSGTYPE_L2_TRADE                          (逐笔成交)
        - MDS_MSGTYPE_L2_ORDER                          (逐笔委托 (仅深圳))
        - MDS_MSGTYPE_L2_MARKET_OVERVIEW                (市场总览消息 (仅上海))
        - MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE          (虚拟集合竞价消息 (仅上海))
        - MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL        (增量更新消息, 仅在 TickType 为 AllIncrements 时存在 (仅上海))
        - MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL        (增量更新消息, 仅在 TickType 为 AllIncrements 时存在 (仅上海))
    3. 可以参考样例代码:
        - mds_subscribe_sample.c 样例文件中的函数 MdsApiSample_HandleMsg
        - 或者, mds_client_sample.c 样例文件中的函数 _MdsApiSample_HandleMsg

MDS_0.12.8.2 / 2017-05-16 (ChangeLog)
==============================================

  * 添加 '逐笔数据丢失消息(MdsL2TickLostT)', 以通知下游系统逐笔数据(逐笔成交/逐笔委托)发生了数据丢失, 并且无法重建, 将放弃这些丢失的逐笔数据

MDS_0.12.8.1 / 2017-04-24 (ChangeLog)
==============================================

### 领域模型相关的变更
    - 删除独立的 MdsMktDataSnapshotEntryMetaT 结构体,
      将字段整合到 MdsMktDataSnapshotHeadT 中, 并删除原 meta.priceUnit (价格单位) 字段
    - 重命名 MdsMktDataSnapshotEntryT -> MdsL1SnapshotBodyT
    - 重命名 MdsIndexDataSnapshotEntryT -> MdsIndexSnapshotBodyT
    - 重命名 MdsStockDataSnapshotEntryT -> MdsStockSnapshotBodyT
    - 重命名 MdsStockSnapshotBodyT.PreCloseIOPV -> NAV
    - 重定义 MdsStockSnapshotBodyT.PriceLevel[5] -> BidLevels[5] + OfferLevels[5]
        - ``PriceLevel\[(\w+)\].BuyPrice -> BidLevels[\1].Price``
        - ``PriceLevel\[(\w+)\].BuyVolume -> BidLevels[\1].OrderQty``
        - ``PriceLevel\[(\w+)\].SellPrice -> OfferLevels[\1].Price``
        - ``PriceLevel\[(\w+)\].SellVolume -> OfferLevels[\1].OrderQty``
    - 重命名 MdsStockSnapshotBodyT.TradeVolume -> TotalVolumeTraded
    - 重命名 MdsIndexSnapshotBodyT.TradeVolume -> TotalVolumeTraded
    - 删除 MdsStockSnapshotBodyT.MDStreamID, MdsIndexSnapshotBodyT.MDStreamID 字段
    - 为'市场状态'和'证券实时状态'消息添加 __exchSendingTime, __mdsRecvTime 字段，
      以方便比对实际的行情延时

### 通信协议相关的变更
    - 重新定义消息类型的取值
    - 将证券行情全幅消息拆分为'Level1市场行情快照'、'指数行情快照'、'期权行情快照'三个消息:
        - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH
        - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH
        - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH
    - 调整订阅类型（TickType）的枚举类型定义和取值
        - 重定义 MDS_TICK_TYPE_LATEST_ONLY -> MDS_TICK_TYPE_LATEST_SIMPLIFIED
            - 只订阅最新的行情快照数据, 并忽略和跳过已经过时的数据 (推送的数据量最小, 不会重复发送最新快照)
        - 重定义 MDS_TICK_TYPE_ALL_TICK -> MDS_TICK_TYPE_ALL_INCREMENTS
            - 订阅所有时点的行情快照数据 (需要注意的是，在该模式下将会额外发送Level2行情快照的增量更新消息)
        - 新增 MDS_TICK_TYPE_LATEST_TIMELY
            - 只订阅最新的行情快照数据, 并立即发送最新数据 (会更及时的获取到交易活跃的最新行情, 但会重复发送最新快照)
    - 为了方便使用, 扩大每个订阅请求中能同时指定的产品数量至: 4000
    - 重新定义行情订阅消息
        - 订阅模式 @see eMdsSubscribeModeT
        - 市场和证券类型订阅标志 @see eMdsMktSubscribeFlagT
        - 数据模式 @see eMdsSubscribedTickTypeT
        - 数据种类 @see eMdsSubscribeDataTypeT
        - 开始时间 (-1: 从头开始获取, 0: 从最新位置开始获取实时行情, >0: 从指定的起始时间开始获取)
        - 是否需要初始的行情数据

### API接口相关的变更
    - 重命名 MdsApi_SubscribeMarketData -> MdsApi_SyncSubscribeOnLogon
    - 重命名 MdsApi_ResubscribeMarketData -> MdsApi_SubscribeMarketData
    - 添加辅助的行情订阅接口
        - MdsApi_SubscribeByString
        - MdsApi_SubscribeByStringAndPrefixes
        - MdsHelper_SetSubscribeRequestMode
        - MdsHelper_SetSubscribeRequestTickType
        - MdsHelper_SetSubscribeRequestDataTypes

MDS_0.12.6.3 / 2017-03-24
================================

  * 增加mds_api.h中的头文件引用，API使用者不再需要显式引用sutil库的头文件

MDS_0.12.3 / 2017-02-21
================================

  * 精简API依赖的头文件，并最小化API发布包中的头文件数量
  * 重命名 protocol_parser/errors/mds_protocol_errors.h -> errors/mds_errors.h
  * 重构 MdsApi_GetErrorMsg 方法，支持统一返回业务错误或系统错误信息
  * fix: 修复API解析订阅配置时，交易所代码赋值错误的BUG
  * 添加辅助实现实时行情订阅功能的接口和样例代码
     - MdsApi_ResubscribeMarketData
     - MdsHelper_ClearSubscribeRequestEntries
     - MdsHelper_AddSubscribeRequestEntry
     - 样例代码: mds_subscribe_sample.c

MDS_0.12.1 / 2016-12-21
================================

  * 查询接口重命名
     - MdsApi_QryMktDataSnapshot -> MdsApi_QueryMktDataSnapshot
     - MdsApi_QrySecurityStatus -> MdsApi_QuerySecurityStatus
     - MdsApi_QryTrdSessionStatus -> MdsApi_QueryTrdSessionStatus
  * 删除 MdsApi_IsBusinessError 接口，查询接口不再返回小于 -1000 的错误
  * 查询接口返回值变更:
     - 无数据返回 SPK_NEG(ENOENT)
     - 查询被服务器拒绝返回 SPK_NEG(EINVAL)，具体错误信息通过日志打印

MDS_0.12 / 2016-12-06
==============================

  * 重构错误号定义，使错误号从1000开始
  * 增加 MdsApi_GetErrorMsg 和 MdsApi_GetErrorMsg2 方法
  * 在登录报文中增加协议版本号信息, 并在登录时校验协议版本号的兼容性
