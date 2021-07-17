# MDS-API Update Guide    {#update_guide}

MDS_0.17.0.9 / 2021-04-27
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. fix: 在上海增量快照中增加最高价/最低价字段，以修复可能会丢失增量快照中的最高价/最低价变化的问题
  3. fix: 增加对Windows下的CPU绑定操作的支持, 并完善Windows下的进程号、线程号处理
  4. 增加对上交所逐笔委托行情的支持:
     - 增加行情消息类型: Level2 上交所逐笔委托行情 (MDS_MSGTYPE_L2_SSE_ORDER, 仅适用于上交所)
     - 增加可订阅的数据种类: 上交所逐笔委托 (MDS_SUB_DATA_TYPE_L2_SSE_ORDER, 仅适用于上交所)
  5. 为异步API增加内置的查询通道，并整合查询通道管理和查询接口到异步API中
     - 增加查询通道相关的配置接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsAsyncApi_SetBuiltinQueryable       | 设置是否启用内置的查询通道 (即启动异步API时自动创建一个内置的查询通道) |
       | MdsAsyncApi_IsBuiltinQueryable        | 返回是否启用内置的查询通道 |
       | MdsAsyncApi_SetBuiltinQueryChannelCfg | 设置内置的查询通道的配置信息 |
       | MdsAsyncApi_LoadBuiltinQueryChannelCfg| 从配置文件中加载内置的查询通道的配置信息 |
       | MdsAsyncApi_GetBuiltinQueryChannelCfg | 返回内置的查询通道的配置信息 |
       | MdsAsyncApi_GetBuiltinQueryChannelRef | 返回内置的查询通道的会话信息 |

     - 增加异步API查询接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsAsyncApi_QueryMktDataSnapshot      | 查询证券行情快照 |
       | MdsAsyncApi_QuerySnapshotList         | 批量查询行情快照 |
       | MdsAsyncApi_QuerySnapshotList2        | 批量查询行情快照 |
       | MdsAsyncApi_QuerySecurityStatus       | 查询(深圳)证券实时状态 |
       | MdsAsyncApi_QueryTrdSessionStatus     | 查询(上证)市场状态 |
       | MdsAsyncApi_QueryStockStaticInfoList  | 批量查询证券(股票/债券/基金)静态信息列表 |
       | MdsAsyncApi_QueryStockStaticInfoList2 | 批量查询证券(股票/债券/基金)静态信息列表 |

     - 样例代码参见: samples/mds_sample/01_mds_async_tcp_sample.c

  6. 增加辅助的异步API接口, 以支持对通信线程、回调线程等异步API线程进行初始化处理
       | API                                       | 描述 |
       | ------------------------------------------| -------------------- |
       | MdsAsyncApi_SetOnCommunicationThreadStart | 设置通信线程的线程初始化回调函数 |
       | MdsAsyncApi_SetOnCallbackThreadStart      | 设置回调线程的线程初始化回调函数 |
       | MdsAsyncApi_SetOnIoThreadStart            | 设置异步I/O线程的线程初始化回调函数 |

  7. 增加辅助的行情订阅和会话管理接口
       | API                                       | 描述 |
       | ------------------------------------------| -------------------- |
       | MdsAsyncApi_DefaultOnConnect              | 连接完成后处理的默认实现 (执行默认的行情订阅处理) |
       | MdsAsyncApi_SubscribeByQuery              | 查询证券静态信息并根据查询结果订阅行情信息 (异步API) |
       | MdsApi_SubscribeByQuery                   | 查询证券静态信息并根据查询结果订阅行情信息 (同步API) |
       | MdsApi_GetClientId                        | 返回通道对应的客户端编号 |
       | MdsHelper_AddSubscribeRequestEntry2       | 添加待订阅产品到订阅信息中 (没有数量限制) |
  8. 调整UDP行情组播的心跳间隔时间为: 10秒 (如果超过3倍心跳时间没有收到任何组播消息, 就可以认为组播链路有故障)
  9. 增加对组播地址连接的高可用处理, 为异步API增加组播地址的自动切换处理 (连接异常时自动尝试下一个组播地址), 为同步API增加相应的辅助接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsApi_SetUdpReconnectFromNextAddrAble| 设置重建连接组播通道时是否从下一个地址开始尝试 |
       | MdsApi_IsUdpReconnectFromNextAddrAble | 返回重建连接组播通道时是否从下一个地址开始尝试 |

### 2. 服务端更新概要

  1. 修复可能会丢失上海增量快照中的最高价/最低价变化的问题
  2. 修复个别场景下当委托数量没有变化时会遗漏上证L2快照中的‘价位总委托笔数’变化的问题
  3. 增加对上交所逐笔委托行情的支持
  4. 其它细节完善和优化

### 3. 注意事项

  1. 如果使用的是旧版本的API, 那么服务器端将不再推送上交所Level2快照的增量更新消息, 将只推送全量快照。如果需要使用增量更新消息, 就需要升级到最新版本。
  2. 逐笔成交和逐笔委托结构体中有两个内部使用的字段发生变化:
     - 调整内部字段 '内部频道号 (__channelNo)' 的定义顺序, 如果使用了该字段就需要升级到最新版本；
     - 删除内部字段 '对应的原始行情的序列号 (__origTickSeq)', 该字段没有业务含义通常不会被使用到, 如果使用了该字段, 需要修改或删除相关代码。


---

MDS_0.16.2.1 / 2021-04-20
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. fix: 在上海增量快照中增加最高价/最低价字段，以修复可能会丢失增量快照中的最高价/最低价变化的问题
  3. fix: 增加对Windows下的CPU绑定操作的支持, 并完善Windows下的进程号、线程号处理
  4. 增加对上交所逐笔委托行情的支持:
     - 增加行情消息类型: Level2 上交所逐笔委托行情 (MDS_MSGTYPE_L2_SSE_ORDER, 仅适用于上交所)
     - 增加可订阅的数据种类: 上交所逐笔委托 (MDS_SUB_DATA_TYPE_L2_SSE_ORDER, 仅适用于上交所)
  5. 为异步API增加内置的查询通道，并整合查询通道管理和查询接口到异步API中
     - 增加查询通道相关的配置接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsAsyncApi_SetBuiltinQueryable       | 设置是否启用内置的查询通道 (即启动异步API时自动创建一个内置的查询通道) |
       | MdsAsyncApi_IsBuiltinQueryable        | 返回是否启用内置的查询通道 |
       | MdsAsyncApi_SetBuiltinQueryChannelCfg | 设置内置的查询通道的配置信息 |
       | MdsAsyncApi_LoadBuiltinQueryChannelCfg| 从配置文件中加载内置的查询通道的配置信息 |
       | MdsAsyncApi_GetBuiltinQueryChannelCfg | 返回内置的查询通道的配置信息 |
       | MdsAsyncApi_GetBuiltinQueryChannelRef | 返回内置的查询通道的会话信息 |

     - 增加异步API查询接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsAsyncApi_QueryMktDataSnapshot      | 查询证券行情快照 |
       | MdsAsyncApi_QuerySnapshotList         | 批量查询行情快照 |
       | MdsAsyncApi_QuerySnapshotList2        | 批量查询行情快照 |
       | MdsAsyncApi_QuerySecurityStatus       | 查询(深圳)证券实时状态 |
       | MdsAsyncApi_QueryTrdSessionStatus     | 查询(上证)市场状态 |
       | MdsAsyncApi_QueryStockStaticInfoList  | 批量查询证券(股票/债券/基金)静态信息列表 |
       | MdsAsyncApi_QueryStockStaticInfoList2 | 批量查询证券(股票/债券/基金)静态信息列表 |

     - 样例代码参见: samples/mds_sample/01_mds_async_tcp_sample.c

  6. 增加辅助的异步API接口, 以支持对通信线程、回调线程等异步API线程进行初始化处理
       | API                                       | 描述 |
       | ------------------------------------------| -------------------- |
       | MdsAsyncApi_SetOnCommunicationThreadStart | 设置通信线程的线程初始化回调函数 |
       | MdsAsyncApi_SetOnCallbackThreadStart      | 设置回调线程的线程初始化回调函数 |
       | MdsAsyncApi_SetOnIoThreadStart            | 设置异步I/O线程的线程初始化回调函数 |

  7. 增加辅助的行情订阅和会话管理接口
       | API                                       | 描述 |
       | ------------------------------------------| -------------------- |
       | MdsAsyncApi_DefaultOnConnect              | 连接完成后处理的默认实现 (执行默认的行情订阅处理) |
       | MdsAsyncApi_SubscribeByQuery              | 查询证券静态信息并根据查询结果订阅行情信息 (异步API) |
       | MdsApi_SubscribeByQuery                   | 查询证券静态信息并根据查询结果订阅行情信息 (同步API) |
       | MdsApi_GetClientId                        | 返回通道对应的客户端编号 |
       | MdsHelper_AddSubscribeRequestEntry2       | 添加待订阅产品到订阅信息中 (没有数量限制) |
  8. 调整UDP行情组播的心跳间隔时间为: 10秒 (如果超过3倍心跳时间没有收到任何组播消息, 就可以认为组播链路有故障)
  9. 增加对组播地址连接的高可用处理, 为异步API增加组播地址的自动切换处理 (连接异常时自动尝试下一个组播地址), 为同步API增加相应的辅助接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsApi_SetUdpReconnectFromNextAddrAble| 设置重建连接组播通道时是否从下一个地址开始尝试 |
       | MdsApi_IsUdpReconnectFromNextAddrAble | 返回重建连接组播通道时是否从下一个地址开始尝试 |

### 2. 服务端更新概要

  1. 修复可能会丢失上海增量快照中的最高价/最低价变化的问题
  2. 修复个别场景下当委托数量没有变化时会遗漏上证L2快照中的‘价位总委托笔数’变化的问题
  3. 增加对上交所逐笔委托行情的支持
  4. 其它细节完善和优化

### 3. 注意事项

  1. 如果使用的是旧版本的API, 那么服务器端将不再推送上交所Level2快照的增量更新消息, 将只推送全量快照。如果需要使用增量更新消息, 就需要升级到最新版本。
  2. 逐笔成交和逐笔委托结构体中有两个内部使用的字段发生变化:
     - 调整内部字段 '内部频道号 (__channelNo)' 的定义顺序, 如果使用了该字段就需要升级到最新版本；
     - 删除内部字段 '对应的原始行情的序列号 (__origTickSeq)', 该字段没有业务含义通常不会被使用到, 如果使用了该字段, 需要修改或删除相关代码。


---

MDS_0.16.1.9 / 2020-11-20
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
    - 如果使用到了时间戳字段下的微秒时间, 则至少需要升级到v0.16.1.2版本。具体请参见 v0.16.1.2 版本的更新说明
  2. 证券静态信息 (MdsStockStaticInfoT) 中新增证券子类型:
    - 新增 基础设施基金(OES_SUB_SECURITY_TYPE_FUND_REITS)
  3. 增加辅助接口
    | API                           | 描述 |
    | ------------------------------| -------------------- |
    | MdsApi_GetClientType          | 返回通道对应的客户端类型 |
    | MdsApi_GetClientStatus        | 返回通道对应的客户端状态 |
    | MdsApi_SetRetainExtDataAble   | 设置是否保留(不清空)由应用层自定义使用的扩展存储空间数据 (__extData) |
    | MdsApi_IsRetainExtDataAble    | 返回是否保留(不清空)由应用层自定义使用的扩展存储空间数据 |

### 2. 服务端更新概要

  1. 无


---

MDS_0.16.1.7 / 2020-09-30
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)
    - 如果使用到了时间戳字段下的微秒时间, 则至少需要升级到v0.16.1.2版本。具体请参见 v0.16.1.2 版本的更新说明
  2. 新增 证券属性定义(eOesSecurityAttributeT) 枚举类型
  3. '证券静态信息(MdsStockStaticInfoT)' 中启用 证券属性 (securityAttribute) 字段

### 2. 服务端更新概要

  1. 无


---

MDS_0.16.1.4 / 2020-08-28
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)
     - 如果使用到了时间戳字段下的微秒时间, 则需要升级最新的API, 因为时间戳字段已全部升级为纳秒级时间戳。具体请参见 v0.16.1.2 版本的更新说明
  2. fix: 完备Windows平台下的WSACleanup资源释放处理，避免额外调用WSACleanup导致外部系统的网络操作异常
  3. fix: 修复Win64下不能正确获取纳秒级时间戳的问题
  4. fix: 修复MinGW下 struct timespec 结构体未按64位对齐的问题
  5. fix: 将行情API中的默认集群类型调整为基于复制集的高可用集群, 避免误连接到行情备机
  6. 为异步API增加用于返回尚未被处理的剩余数据数量的辅助接口
    | API                                     | 描述 |
    | ----------------------------------------| -------------------- |
    | MdsAsyncApi_GetAsyncQueueTotalCount     | 返回异步API累计已入队的消息数量 |
    | MdsAsyncApi_GetAsyncQueueRemainingCount | 返回队列中尚未被处理的剩余数据数量 |

### 2. 服务端更新概要

  1. 完善系统在异常场景下24小时持续运行的可靠性
  2. fix: 修复会丢弃部分上海时间戳相同的全量快照 (导致丢失一段时间的最高价/最低价变化), 以及部分时间戳相同但开盘价等有变化的增量快照 (导致丢失一段时间的开盘价信息) 的问题
  3. fix: 进一步重构和完善对上海快照的去重和合并处理, 修复会丢失部分上海最优委托队列和指数快照的问题
  4. fix: 忽略上海L1行情中的综合业务行情数据
  5. 其它细节完善和优化


---

MDS_0.16.1.2 / 2020-07-07
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API (建议升级, 以支持期权业务)
     - 如果使用到了时间戳字段下的微秒时间, 则需要升级最新的API, 因为时间戳字段已全部升级为纳秒级时间戳。具体请参见注意事项说明
  2. fix: 修复在Win32下因为对齐问题导致指针位置不正确的BUG (当启用异步API的异步回调处理时会触发)
  3. 异步API新增如下接口
    | API                                | 描述 |
    | -----------------------------------| -------------------- |
    | MdsAsyncApi_IsAllTerminated        | 检查所有线程是否均已安全退出 |
  4. 同步API新增如下接口
    | API                                | 描述 |
    | -----------------------------------| -------------------- |
    | MdsApi_QueryOptionStaticInfoList   | 批量查询期权合约静态信息列表 |
    | MdsApi_QueryOptionStaticInfoList2  | 批量查询期权合约静态信息列表 (字符串指针数组形式的期权代码列表) |
    | MdsApi_QueryStockStaticInfoList    | 批量查询证券(股票/债券/基金)静态信息列表 |
    | MdsApi_QueryStockStaticInfoList2   | 批量查询证券(股票/债券/基金)静态信息列表 (字符串指针数组形式的证券代码列表) |
    | MdsApi_GetChannelGroupLastRecvTime | 返回通道组最近接收消息时间 |
    | MdsApi_GetChannelGroupLastSendTime | 返回通道组最近发送消息时间 |
    | MdsApi_HasStockStatus              | 返回现货产品是否具有指定状态|
    | __MdsApi_CheckApiVersion           | 检查API版本是否匹配 (检查API头文件和库文件的版本是否匹配) |
  5. 为支持创业板注册制改革, 证券静态信息 (MdsStockStaticInfoT) 中新增如下字段:
    | 字段                        | 描述 |
    | -------------------------- | -------------------- |
    | isRegistration             | 是否注册制 |
    | currType                   | 币种 |
    | qualificationClass         | 投资者适当性管理分类 |
    | securityStatus             | 证券状态 |
    | securityAttribute          | 证券属性 (保留字段) |
    | suspFlag                   | 连续停牌标识 |
    | isDayTrading               | 是否支持当日回转交易 |
    | isCrdMarginTradeUnderlying | 是否为融资标的 |
    | isCrdShortSellUnderlying   | 是否为融券标的 |
    | isCrdCollateral            | 是否为融资融券担保品 |
    | isNoProfit                 | 是否尚未盈利 |
    | isWeightedVotingRights     | 是否存在投票权差异 |
    | isVie                      | 是否具有协议控制框架 |
    | lmtBuyQtyUnit              | 限价买入单位 |
    | lmtSellQtyUnit             | 限价卖出单位 |
    | mktBuyQtyUnit              | 市价买入单位 |
    | mktSellQtyUnit             | 市价卖出单位 |
    | parValue                   | 面值 (重命名 parPrice) |
    | auctionLimitType           | 连续交易时段的有效竞价范围限制类型 |
    | auctionReferPriceType      | 连续交易时段的有效竞价范围基准价类型 |
    | auctionUpDownRange         | 连续交易时段的有效竞价范围涨跌幅度 |
    | listDate                   | 上市日期 |
    | maturityDate               | 到期日期 (仅适用于债券等有发行期限的产品) |
    | underlyingSecurityId       | 基础证券代码 |
    | securityLongName           | 证券长名称 (UTF-8 编码) |
    | securityEnglishName        | 证券英文名称 (UTF-8 编码) |
    | securityIsinCode           | ISIN代码 |
  6. 证券静态信息 (MdsStockStaticInfoT) 中新增证券子类型(同OES):
     - 创业板存托凭证 (OES_SUB_SECURITY_TYPE_STOCK_GEMCDR)
     - 可交换债券 (OES_SUB_SECURITY_TYPE_BOND_EXG)
     - 商品期货ETF (OES_SUB_SECURITY_TYPE_ETF_COMMODITY_FUTURES)
  7. 优化异步API
     - 为异步API增加是否优先使用大页内存来创建异步队列的配置项
     - 为异步API的I/O线程增加追加模式输出的配置项
     - 为异步API的I/O线程增加支持忙等待的配置选项，以使异步队列的延迟统计结果更接近实际情况
  8. 优化时间戳精度, 将系统下的时间戳全部升级为纳秒级时间戳, 以提高时延统计的精度
     - 时间戳字段的数据类型从 STimevalT/STimeval32T 变更为 STimespecT/STimespec32T
     - 协议保持兼容, 但如果使用到了时间戳字段下的微秒时间(tv_usec 字段), 则需要修改为纳秒时间(tv_nsec 字段),
       否则会因为时间单位的调整而导致时延计算错误
  9. API中添加vs2015工程样例

### 2. 服务端更新概要

  1. fix: 更新上海增量快照的去重处理, 以处理存在时间相同但数据不同的增量快照问题
  2. fix: 完善上海增量快照的更新处理, 防止因为数据丢失导致出现买卖盘价格倒挂
  3. fix: 完善由上海增量快照合成的快照消息中，没有更新和携带实际的原始行情的序列号（__origTickSeq）的问题
  4. fix: 修复委托队列增量消息的大小未全部按64位对齐的问题
  5. 支持创业板注册制改革
  6. 其它细节完善和性能优化

### 3. 注意事项说明

  1. 时间戳精度的修改没法完全兼容之前的API, 如果使用到了时间戳字段下的微秒时间(tv_usec 字段), 则需要升级API到最新版本
     - 通常只有在统计延迟时才会使用到微秒时间(tv_usec)字段, 如果使用到了该字段, 则需要改为使用纳秒时间(tv_nsec)字段,
       否则会因为时间单位的调整而导致时延计算错误
     - 升级API以后, 可以通过检查有无编译错误的方式, 来检查是否使用到了 tv_usec 字段。如果没有编译错误就无需再做额外的调整
  2. 上海市场存在更新时间相同但数据不同的Level-2快照, 与通常的预期不太相符。(频率不高, 但会存在这样的数据)


---

MDS_0.16.0.5 / 2020-04-17
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级, 以支持期权业务)
  2. 统一沪深期权行情的昨收盘价字段, 不再通过该字段推送昨结算价（深圳期权快照中没有结算价字段）
  3. 调整组播行情的行为, 不再强制过滤掉重复的快照行情和重建到的逐笔行情, 并允许通过订阅条件进行控制
  4. 为异步API增加对UDP行情数据的本地订阅/过滤功能
      - 订阅方式与TCP行情订阅方式相同, 相关订阅接口如下:
         - MdsAsyncApi_SubscribeMarketData
         - MdsAsyncApi_SubscribeByString
         - MdsAsyncApi_SubscribeByStringAndPrefixes
      - 对UDP行情数据的订阅和过滤功能默认不开启, 可通过接口或配置予以控制
      - 样例代码参见:
         - samples/mds_sample/04_mds_async_udp_sample.c
  5. 调整示例代码的目录位置

### 2. 服务端更新概要

  1. 无


---

MDS_0.16.0.4 / 2020-02-28
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级, 以支持期权业务)
  2. fix: 为API增加对SIGPIPE信号的屏蔽处理，以避免连接断开以后重复send导致程序异常退出
  3. 重构异步API接口, 统一交易和行情的异步API定义 (不兼容之前版本的异步API)
     - 支持异步接收行情数据
     - 支持自动的连接管理 (自动识别异常并重建连接)
     - 支持异步数据落地和延迟统计 (可以通过配置文件进行控制, 默认为禁用)
     - 主要接口:
        - MdsAsyncApi_CreateContext
        - MdsAsyncApi_AddChannel
        - MdsAsyncApi_Start
        - MdsAsyncApi_Stop
        - MdsAsyncApi_ReleaseContext
    - 样例代码参见: mds_api/samples/02_mds_async_api_sample.c

### 2. 服务端更新概要

  1. fix: 修复因为指令乱序而导致快照行情发生数据重复和数据丢失的风险
  2. 其它细节完善

### 3. 注意事项说明

  1. 异步接口发生了变化, 无法兼容之前版本的异步API, 请参考样例代码进行升级处理。


---

MDS_0.16.0.1 / 2019-12-12
-----------------------------------

### 1. API更新概要

  1. 完善异步API的实现机制及其异常处理

### 2. 服务端更新概要

  1. 完善对无效期权行情的处理
  2. 其它细节完善


---

MDS_0.16 / 2019-11-20
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级, 以支持期权业务)
  2. API新增如下接口
    | API                          | 描述
    | ---------------------------- | ---------------
    | MdsApi_QueryOptionStaticInfo | 查询期权静态信息


---

MDS_0.15.12.1 / 2021-04-19
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. fix: 在上海增量快照中增加最高价/最低价字段，以修复可能会丢失增量快照中的最高价/最低价变化的问题
  3. fix: 增加对Windows下的CPU绑定操作的支持, 并完善Windows下的进程号、线程号处理
  4. 增加对上交所逐笔委托行情的支持:
     - 增加行情消息类型: Level2 上交所逐笔委托行情 (MDS_MSGTYPE_L2_SSE_ORDER, 仅适用于上交所)
     - 增加可订阅的数据种类: 上交所逐笔委托 (MDS_SUB_DATA_TYPE_L2_SSE_ORDER, 仅适用于上交所)
  5. 为异步API增加内置的查询通道，并整合查询通道管理和查询接口到异步API中
     - 增加查询通道相关的配置接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsAsyncApi_SetBuiltinQueryable       | 设置是否启用内置的查询通道 |
       | MdsAsyncApi_IsBuiltinQueryable        | 返回是否启用内置的查询通道 |
       | MdsAsyncApi_SetBuiltinQueryChannelCfg | 设置内置的查询通道的配置信息 |
       | MdsAsyncApi_LoadBuiltinQueryChannelCfg| 从配置文件中加载内置的查询通道的配置信息 |
       | MdsAsyncApi_GetBuiltinQueryChannelCfg | 返回内置的查询通道的配置信息 |
       | MdsAsyncApi_GetBuiltinQueryChannelRef | 返回内置的查询通道的会话信息 |

     - 增加异步API查询接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsAsyncApi_QueryMktDataSnapshot      | 查询证券行情快照 |
       | MdsAsyncApi_QuerySnapshotList         | 批量查询行情快照 |
       | MdsAsyncApi_QuerySnapshotList2        | 批量查询行情快照 |
       | MdsAsyncApi_QuerySecurityStatus       | 查询(深圳)证券实时状态 |
       | MdsAsyncApi_QueryTrdSessionStatus     | 查询(上证)市场状态 |
       | MdsAsyncApi_QueryStockStaticInfoList  | 批量查询证券(股票/债券/基金)静态信息列表 |
       | MdsAsyncApi_QueryStockStaticInfoList2 | 批量查询证券(股票/债券/基金)静态信息列表 |

     - 样例代码参见: samples/mds_sample/01_mds_async_tcp_sample.c

  6. 增加辅助的异步API接口, 以支持对通信线程、回调线程等异步API线程进行初始化处理
       | API                                       | 描述 |
       | ------------------------------------------| -------------------- |
       | MdsAsyncApi_SetOnCommunicationThreadStart | 设置通信线程的线程初始化回调函数 |
       | MdsAsyncApi_SetOnCallbackThreadStart      | 设置回调线程的线程初始化回调函数 |
       | MdsAsyncApi_SetOnIoThreadStart            | 设置异步I/O线程的线程初始化回调函数 |

  7. 增加辅助的行情订阅和会话管理接口
       | API                                       | 描述 |
       | ------------------------------------------| -------------------- |
       | MdsAsyncApi_DefaultOnConnect              | 连接完成后处理的默认实现 (执行默认的行情订阅处理) |
       | MdsAsyncApi_SubscribeByQuery              | 查询证券静态信息并根据查询结果订阅行情信息 (异步API) |
       | MdsApi_SubscribeByQuery                   | 查询证券静态信息并根据查询结果订阅行情信息 (同步API) |
       | MdsApi_GetClientId                        | 返回通道对应的客户端编号 |
       | MdsHelper_AddSubscribeRequestEntry2       | 添加待订阅产品到订阅信息中 (没有数量限制) |
  8. 调整UDP行情组播的心跳间隔时间为: 10秒 (如果超过3倍心跳时间没有收到任何组播消息, 就可以认为组播链路有故障)
  9. 增加对组播地址连接的高可用处理, 为异步API增加组播地址的自动切换处理 (连接异常时自动尝试下一个组播地址), 为同步API增加相应的辅助接口
       | API                                   | 描述 |
       | --------------------------------------| -------------------- |
       | MdsApi_SetUdpReconnectFromNextAddrAble| 设置重建连接组播通道时是否从下一个地址开始尝试 |
       | MdsApi_IsUdpReconnectFromNextAddrAble | 返回重建连接组播通道时是否从下一个地址开始尝试 |

### 2. 服务端更新概要

  1. 修复可能会丢失上海增量快照中的最高价/最低价变化的问题
  2. 修复个别场景下当委托数量没有变化时会遗漏上证L2快照中的‘价位总委托笔数’变化的问题
  3. 增加对上交所逐笔委托行情的支持
  4. 其它细节完善和优化

### 3. 注意事项

  1. 如果使用的是旧版本的API, 那么服务器端将不再推送上交所Level2快照的增量更新消息, 将只推送全量快照。如果需要使用增量更新消息, 就需要升级到最新版本。
  2. 逐笔成交和逐笔委托结构体中有两个内部使用的字段发生变化:
     - 调整内部字段 '内部频道号 (__channelNo)' 的定义顺序, 如果使用了该字段就需要升级到最新版本；
     - 删除内部字段 '对应的原始行情的序列号 (__origTickSeq)', 该字段没有业务含义通常不会被使用到, 如果使用了该字段, 需要修改或删除相关代码。


---

MDS_0.15.11.15 / 2020-11-20
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. 证券静态信息 (MdsStockStaticInfoT) 中新增证券子类型:
    - 新增 基础设施基金(OES_SUB_SECURITY_TYPE_FUND_REITS)
  3. 增加辅助接口
    | API                           | 描述 |
    | ------------------------------| -------------------- |
    | MdsApi_GetClientType          | 返回通道对应的客户端类型 |
    | MdsApi_GetClientStatus        | 返回通道对应的客户端状态 |
    | MdsApi_SetRetainExtDataAble   | 设置是否保留(不清空)由应用层自定义使用的扩展存储空间数据 (__extData) |
    | MdsApi_IsRetainExtDataAble    | 返回是否保留(不清空)由应用层自定义使用的扩展存储空间数据 |

### 2. 服务端更新概要

  1. 无


---

MDS_0.15.11.12 / 2020-09-30
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. 新增 证券属性定义(eOesSecurityAttributeT) 枚举类型
  3. '证券静态信息(MdsStockStaticInfoT)' 中启用 证券属性 (securityAttribute) 字段

### 2. 服务端更新概要

  1. fix: 修复会丢弃部分上海时间戳相同的全量快照 (导致丢失一段时间的最高价/最低价变化), 以及部分时间戳相同但开盘价等有变化的增量快照 (导致丢失一段时间的开盘价信息) 的问题
  2. fix: 进一步重构和完善对上海快照的去重和合并处理, 修复会丢失部分上海最优委托队列和指数快照的问题
  3. fix: 忽略上海L1行情中的综合业务行情数据
  4. 其它细节完善和优化


---

MDS_0.15.11.6 / 2020-07-23
-----------------------------------

### 1. API更新概要

  1. 该版本是 v015.11.4 的BUG修复版本, 建议升级到该版本
  2. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)
     - 如果使用到了时间戳字段下的微秒时间, 则需要升级最新的API, 因为时间戳字段已全部升级为纳秒级时间戳。具体请参见 v0.15.11.4 版本的更新说明
  3. fix: 完备Windows平台下的WSACleanup资源释放处理，避免额外调用WSACleanup导致外部系统的网络操作异常
  4. fix: 修复Win64下不能正确获取纳秒级时间戳的问题
  5. fix: 修复MinGW下 struct timespec 结构体未按64位对齐的问题
  6. fix: 将行情API中的默认集群类型调整为基于复制集的高可用集群, 避免误连接到行情备机
  7. 为异步API增加用于返回尚未被处理的剩余数据数量的辅助接口
    | API                                     | 描述 |
    | ----------------------------------------| -------------------- |
    | MdsAsyncApi_GetAsyncQueueTotalCount     | 返回异步API累计已入队的消息数量 |
    | MdsAsyncApi_GetAsyncQueueRemainingCount | 返回队列中尚未被处理的剩余数据数量 |

### 2. 服务端更新概要

  1. 完善系统在异常场景下24小时持续运行的可靠性
  2. 其它细节完善和优化


---

MDS_0.15.11.4 / 2020-07-07
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级以支持创业板注册制改革的相关内容)
     - 如果使用到了时间戳字段下的微秒时间, 则需要升级最新的API, 因为时间戳字段已全部升级为纳秒级时间戳。具体请参见注意事项说明
  2. fix: 修复在Win32下因为对齐问题导致指针位置不正确的BUG (当启用异步API的异步回调处理时会触发)
  3. 异步API新增如下接口
    | API                                | 描述 |
    | -----------------------------------| -------------------- |
    | MdsAsyncApi_IsAllTerminated        | 检查所有线程是否均已安全退出 |
  4. 同步API新增如下接口
    | API                                | 描述 |
    | -----------------------------------| -------------------- |
    | MdsApi_QueryStockStaticInfoList    | 批量查询证券(股票/债券/基金)静态信息列表 |
    | MdsApi_QueryStockStaticInfoList2   | 批量查询证券(股票/债券/基金)静态信息列表 (字符串指针数组形式的证券代码列表) |
    | MdsApi_GetChannelGroupLastRecvTime | 返回通道组最近接收消息时间 |
    | MdsApi_GetChannelGroupLastSendTime | 返回通道组最近发送消息时间 |
    | MdsApi_HasStockStatus              | 返回现货产品是否具有指定状态|
    | __MdsApi_CheckApiVersion           | 检查API版本是否匹配 (检查API头文件和库文件的版本是否匹配) |
  5. 为支持创业板注册制改革, 证券静态信息 (MdsStockStaticInfoT) 中新增如下字段:
    | 字段                        | 描述 |
    | -------------------------- | -------------------- |
    | isRegistration             | 是否注册制 |
    | currType                   | 币种 |
    | qualificationClass         | 投资者适当性管理分类 |
    | securityStatus             | 证券状态 |
    | securityAttribute          | 证券属性 (保留字段) |
    | suspFlag                   | 连续停牌标识 |
    | isDayTrading               | 是否支持当日回转交易 |
    | isCrdMarginTradeUnderlying | 是否为融资标的 |
    | isCrdShortSellUnderlying   | 是否为融券标的 |
    | isCrdCollateral            | 是否为融资融券担保品 |
    | isNoProfit                 | 是否尚未盈利 |
    | isWeightedVotingRights     | 是否存在投票权差异 |
    | isVie                      | 是否具有协议控制框架 |
    | lmtBuyQtyUnit              | 限价买入单位 |
    | lmtSellQtyUnit             | 限价卖出单位 |
    | mktBuyQtyUnit              | 市价买入单位 |
    | mktSellQtyUnit             | 市价卖出单位 |
    | parValue                   | 面值 (重命名 parPrice) |
    | auctionLimitType           | 连续交易时段的有效竞价范围限制类型 |
    | auctionReferPriceType      | 连续交易时段的有效竞价范围基准价类型 |
    | auctionUpDownRange         | 连续交易时段的有效竞价范围涨跌幅度 |
    | listDate                   | 上市日期 |
    | maturityDate               | 到期日期 (仅适用于债券等有发行期限的产品) |
    | underlyingSecurityId       | 基础证券代码 |
    | securityLongName           | 证券长名称 (UTF-8 编码) |
    | securityEnglishName        | 证券英文名称 (UTF-8 编码) |
    | securityIsinCode           | ISIN代码 |
  6. 证券静态信息 (MdsStockStaticInfoT) 中新增证券子类型(同OES):
     - 创业板存托凭证 (OES_SUB_SECURITY_TYPE_STOCK_GEMCDR)
     - 可交换债券 (OES_SUB_SECURITY_TYPE_BOND_EXG)
     - 商品期货ETF (OES_SUB_SECURITY_TYPE_ETF_COMMODITY_FUTURES)
  7. 优化异步API
     - 为异步API增加是否优先使用大页内存来创建异步队列的配置项
     - 为异步API的I/O线程增加追加模式输出的配置项
     - 为异步API的I/O线程增加支持忙等待的配置选项，以使异步队列的延迟统计结果更接近实际情况
  8. 优化时间戳精度, 将系统下的时间戳全部升级为纳秒级时间戳, 以提高时延统计的精度
     - 时间戳字段的数据类型从 STimevalT/STimeval32T 变更为 STimespecT/STimespec32T
     - 协议保持兼容, 但如果使用到了时间戳字段下的微秒时间(tv_usec 字段), 则需要修改为纳秒时间(tv_nsec 字段), 
       否则会因为时间单位的调整而导致时延计算错误
  9. API中添加vs2015工程样例

### 2. 服务端更新概要

  1. fix: 更新上海增量快照的去重处理, 以处理存在时间相同但数据不同的增量快照问题
  2. fix: 完善上海增量快照的更新处理, 防止因为数据丢失导致出现买卖盘价格倒挂
  3. fix: 完善由上海增量快照合成的快照消息中，没有更新和携带实际的原始行情的序列号（__origTickSeq）的问题
  4. fix: 修复委托队列增量消息的大小未全部按64位对齐的问题
  5. 支持创业板注册制改革
  6. 其它细节完善和性能优化

### 3. 注意事项说明

  1. 时间戳精度的修改没法完全兼容之前的API, 如果使用到了时间戳字段下的微秒时间(tv_usec 字段), 则需要升级API到最新版本
     - 通常只有在统计延迟时才会使用到微秒时间(tv_usec)字段, 如果使用到了该字段, 则需要改为使用纳秒时间(tv_nsec)字段, 
       否则会因为时间单位的调整而导致时延计算错误
     - 升级API以后, 可以通过检查有无编译错误的方式, 来检查是否使用到了 tv_usec 字段。如果没有编译错误就无需再做额外的调整
  2. 上海市场存在更新时间相同但数据不同的Level-2快照, 与通常的预期不太相符。(频率不高, 但会存在这样的数据)


---

MDS_0.15.10.5 / 2020-04-07
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. fix: 为API增加对SIGPIPE信号的屏蔽处理，以避免连接断开以后重复send导致程序异常退出
  3. 统一沪深期权行情的昨收盘价字段，不再通过该字段推送昨结算价（深圳期权快照中没有结算价字段）
  4. 调整组播行情的行为, 不再强制过滤掉重复的快照行情和重建到的逐笔行情，并允许通过订阅条件进行控制
  5. 重构异步API接口, 统一交易和行情的异步API定义 (不兼容之前版本的异步API)
     - 支持异步接收行情数据
     - 支持自动的连接管理 (自动识别异常并重建连接)
     - 支持异步数据落地和延迟统计 (可以通过配置文件进行控制, 默认为禁用)
     - 主要接口:
        - MdsAsyncApi_CreateContext
        - MdsAsyncApi_AddChannel
        - MdsAsyncApi_Start
        - MdsAsyncApi_Stop
        - MdsAsyncApi_ReleaseContext
     - 样例代码参见:
         - mds_api/samples/mds_sample/01_mds_async_tcp_sample.c
  6. 为异步API增加对UDP行情数据的本地订阅/过滤功能
      - 订阅方式与TCP行情订阅方式相同, 相关订阅接口如下:
         - MdsAsyncApi_SubscribeMarketData
         - MdsAsyncApi_SubscribeByString
         - MdsAsyncApi_SubscribeByStringAndPrefixes
      - 对UDP行情数据的订阅和过滤功能默认不开启, 可通过接口或配置予以控制
      - 样例代码参见:
         - mds_api/samples/mds_sample/03_mds_async_udp_sample.c
  7. 调整示例代码的目录位置

### 2. 服务端更新概要

  1. fix: 修复因为指令乱序而导致快照行情发生数据重复和数据丢失的风险
  2. 其它细节完善和性能优化

### 3. 注意事项说明

  1. 异步接口发生了变化, 无法兼容之前版本的异步API, 请参考样例代码进行升级处理


---

MDS_0.15.9.4 / 2019-12-24
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. 证券静态信息结构体中增加字段 '总股本(outstandingShare)' 和 '流通股数量(publicFloatShare)' (API保持兼容)
  3. 行情数据类型(eMdsMdStreamTypeT)中新增类型 '深交所国证指数快照行情 (MDS_MD_STREAM_TYPE_SZSE_CN_INDEX)'
  4. 调整指数快照行情中今收盘指数(CloseIdx)字段的注释信息, 深圳指数快照行情也将提供收盘指数
  5. 调整行情组播频道的划分, 划分为两个独立的沪/深快照频道和两个独立的沪/深逐笔频道, 共4个组播频道 (API及配置文件保持兼容, 但频道内容发生了变化)
     - 快照-频道1 (Snap1): 上海L1/L2快照
     - 快照-频道2 (Snap2): 深圳L1/L2快照
     - 逐笔-频道1 (Tick1): 上海逐笔成交
     - 逐笔-频道2 (Tick2): 深圳逐笔成交/逐笔委托

### 2. 服务端更新概要

  1. fix: 为深圳逐笔委托中的委托价格增加最大价格上限(1999999999)。如果逐笔委托中的委托价格超出该值, 则将赋值为该值, 避免当委托价格过大时溢出为负数
  2. 增加对深交所国证指数快照行情的支持
  3. 调整行情组播频道的划分, 划分为两个独立的沪/深快照频道和两个独立的沪/深逐笔频道, 共4个组播频道 (API及配置文件保持兼容, 但频道内容发生了变化)
  4. 其它细节完善

### 3. 注意事项说明

  1. 行情组播频道做了调整, 沪深的快照和逐笔都将分别通过不同的独立频道广播
     - 快照-频道1 (Snap1): 上海L1/L2快照
     - 快照-频道2 (Snap2): 深圳L1/L2快照
     - 逐笔-频道1 (Tick1): 上海逐笔成交
     - 逐笔-频道2 (Tick2): 深圳逐笔成交/逐笔委托
  2. 行情数据类型(eMdsMdStreamTypeT)中新增了数据类型 '深交所国证指数快照行情 (MDS_MD_STREAM_TYPE_SZSE_CN_INDEX)',
     可以通过该类型来区分普通指数快照和国证指数快照。


---

MDS_0.15.9.1 / 2019-08-16
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. 增加异步API接口, 以支持行情异步接收和处理
     - 支持异步行情接收
     - 支持自动的连接管理 (自动识别异常并重建连接)
     - 样例代码参见: mds_api/samples/01_mds_async_tcp_sample.c
  3. 增加对重建到的逐笔数据的订阅和推送处理
     - 行情订阅条件和订阅配置中增加 '逐笔数据的数据重建标识 tickRebuildFlag', 用于标识是否订阅重建到的逐笔数据
  4. 增加批量订阅模式, 以支持更灵活可控的行情订阅 (@see eMdsSubscribeModeT)
  5. 完善对行情订阅条件中起始时间和初始行情标志的支持, 允许在会话过程中的任意时间指定 beginTime 和 isRequireInitialMktData 订阅参数
  6. 增加为SubscribeByString设置附加订阅参数的API接口
     - MdsApi_SetThreadSubscribeTickType
     - MdsApi_SetThreadSubscribeTickRebuildFlag
     - MdsApi_SetThreadSubscribeTickExpireType
     - MdsApi_SetThreadSubscribeRequireInitMd
     - MdsApi_SetThreadSubscribeBeginTime
  7. 增加可以禁止API在登录后自动执行行情订阅操作的接口
     - MdsApi_SetThreadAutoSubscribeOnLogon
  8. 增加用于解析CVS格式行情数据文件的辅助API接口
     - MdsCsvParser_DecodeCsvRecord
  9. 新增错误码1037、1038
     | 错误码 | 描述 |
     | ---- | --------------- |
     | 1037 | 集群编号不匹配 |
     | 1038 | 无此操作权限 |
  10. 替换头文件中使用的 likely/unlikely 关键字, 以避免与第三方库的同名函数冲突
      - 若编译时提示 likely 与 boost 库中的函数名称冲突, 可以通过指定宏 __NO_SHORT_LIKELY 来解决

### 2. 服务端更新概要

  1. 修复和优化逐笔行情的数据重建处理
  2. 其它细节完善


---

MDS_0.15.9 / 2019-05-31
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级, 以兼容深圳证券业务开关数量的调整)
  2. fix: 修复API无法支持取值大于1024的文件描述符的问题
  3. 扩大深圳证券业务开关的最大数量, 以应对行情数据内容的更新
     - 该修改可能会对之前版本的API造成影响: 会影响到证券实时状态消息的延迟计算, 旧版本会读取到无效的打点时间
  4. 调整行情数据类型(mdStreamType, eMdsMdStreamTypeT)的取值, 使其可以标识出快照行情的具体数据类型
     - 该修改会存在兼容性问题, 客户端程序可以通过编译错误来识别需要调整的地方 (如果没有编译错误就不需要调整)
     - 行情数据类型的取值将尽量与消息类型保持一致, 但以下类型比较特殊：
       - 深圳成交量统计指标
       - 上交所 Level1 行情快照-债券
       - 上交所 Level1 行情快照-基金
  5. 重命名 securityType => mdProductType, 以避免与交易端的证券类型混淆
    - securityType => mdProductType
    - eMdsSecurityTypeT => eMdsMdProductTypeT
  6. 删除已经废弃的虚拟集合竞价消息的消息定义和数据类型定义
  7. API新增如下接口
     | API                          | 描述
     | ---------------------------- | ---------------
     | MdsApi_QueryStockStaticInfo  | 查询证券(股票/债券/基金)静态信息
     | MdsApi_QuerySnapshotList     | 批量查询行情快照接口
     | MdsApi_InitAllByCfgStruct    | 按照配置信息结构体初始化客户端环境接口
     | MdsApi_SendChangePasswordReq | 修改客户端登录密码
     | MdsApi_SetCustomizedIp       | 设置客户端自定义的本地IP地址
     | MdsApi_GetCustomizedIp       | 获取客户端自定义的本地IP
     | MdsApi_SetCustomizedMac      | 设置客户端自定义的本地MAC地址
     | MdsApi_GetCustomizedMac      | 获取客户端自定义的本地MAC
     | MdsApi_SetCustomizedDriverId | 设置客户端自定义的本地设备序列号
     | MdsApi_GetCustomizedDriverId | 获取客户端自定义的本地设备序列号
  8. 新增错误码1029、1034、1035、1036, 调整错误码1007、1022的描述信息
     | 错误码 | 描述
     | ---- | ---------------
     | 1007 | 非服务开放时间
     | 1022 | 尚不支持或尚未开通此业务
     | 1029 | 密码未改变
     | 1034 | 密码强度不足
     | 1035 | 非法的产品类型
     | 1036 | 未通过黑白名单检查

### 2. 服务端更新概要

  1. fix: 修复上海L2快照初始的最低价没有被设置的问题
  2. fix: 解决 MdsApi_SubscribeByString 接口的字符串缓存太小, 最多只能订阅14000只证券的问题
  3. fix: 取消不必要的期权行情降噪处理, 以修复期权行情数量相对较少的问题（35%）
  4. fix: 修复在追加订阅行情时, 会把全市场订阅标志冲掉的问题
  5. fix: 修复市场总览行情中交易所发送时间为负数的问题
  6. 完善单条行情快照查询, 允许对交易所代码和行情数据进行模糊匹配(不必再明确指定交易所代码);
     并且当不存在L1快照时将尝试检索L2快照, 而查询结果统一转换为五档快照返回
  7. 调整L2逐笔数据的行情组播频道, 按照频道号混合推送逐笔成交和逐笔委托, 取代之前逐笔成交/逐笔委托分别推送的方式(API保持兼容, 但频道的内容发生了变化)
     - 快照-频道1 (L1): L1快照/指数/期权 (沪深Level-1快照)
     - 快照-频道2 (L2): L2快照 (沪深Level-2快照)
     - 逐笔-频道1 (Tick1): L2逐笔-频道1 (沪深逐笔成交/逐笔委托)
     - 逐笔-频道2 (Tick2): L2逐笔-频道2 (沪深逐笔成交/逐笔委托)
  8. 优化快照行情的去重处理
  9. 修复其他系统缺陷, 完善安全机制

### 3. 注意事项说明

  1. 以下两处重构可能会引起编译错误, 这两个字段通常不会使用, 可以通过编译错误来识别是否有需要调整的地方, 如果没有编译错误就不需要调整
     - 重命名 securityType => mdProductType
     - 调整行情数据类型(mdStreamType, eMdsMdStreamTypeT)的取值
  2. 服务器端对L2逐笔数据的行情组播频道做了调整, 将按照频道号混合推送逐笔成交和逐笔委托, 以保留逐笔委托和逐笔成交之间时序关系
     - 之前的逐笔成交/逐笔委托是通过两个频道分别推送的, 需要留意调整以后对处理逻辑是否有影响
  3. 服务器端对快照行情的去重处理进行了优化
     - 当以 tickType=0 的模式订阅行情时, 服务器端会对重复的快照行情做去重处理, 不会再推送重复的数据
     - 如果需要获取到所有时点的快照, 可以使用 tickType=1 的模式订阅行情。该模式会和之前版本的行为保持一致, 只要行情时间有变化, 即使数据重复也会对下游推送


---

MDS_0.15.7.4 / 2018-08-31
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API，客户可以选择不升级 (建议升级)
  2. fix: 修复当多个线程同时初始化API日志时, 会导致日志信息重复输出的问题
  3. API新增如下接口
    | API                          | 描述
    | ---------------------------- | ---------------
    | MdsApi_SetLastError          | 设置当前线程的API错误号
    | MdsApi_GetLastError          | 获取当前线程最近一次API调用失败的错误号
    | MdsApi_HasMoreCachedData     | 获取回报通道中尚未被回调函数处理的缓存数据长度
    | MdsApi_SetThreadUsername     | 设置当前线程的登录用户名
    | MdsApi_SetThreadPassword     | 设置当前线程的登录密码
  4. 新增部分错误码
    | 错误码 | 描述
    | ---- | ---------------
    | 1031 | 非法的加密类型
    | 1033 | 无可用节点
  5. 重构 SubscribeByString 接口, 增强行情订阅的灵活性
  6. 增加可订阅的数据种类 (DataType), 以支持单独订阅指数行情和期权行情
  7. 增加可以处理压缩过的消息的 MdsApi_WaitOnMsgCompressible 接口, 以支持对接压缩后的行情数据

### 2. 服务端更新概要

  1. fix: 修复上海L2增量快照中最低价没有正确更新(长时间为0)的BUG
  2. fix: 修复行情订阅列表的计数器缺陷（把相同的证券代码分别作为指数代码和股票代码指定了两遍时，会订阅不到指数行情的问题）
  3. fix: 修复没有拦截掉9:25前后已经过时的虚拟集合竞价消息的问题
  4. 修复其他系统缺陷，完善管理功能和故障恢复处理


---

MDS_0.15.5.16 / 2018-08-31
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)
  2. fix: 修复当多个线程同时初始化API日志时, 会导致日志信息重复输出的问题
  3. 增加 MdsApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
  4. 增加 MdsApi_GetLastError 接口, 用于返回最近一次API调用失败的错误号
  5. 增加设置当前线程登录用户名/登录密码的接口
  6. 重构 SubscribeByString 接口, 增强行情订阅的灵活性
  7. 增加可订阅的数据种类 (DataType), 以支持单独订阅指数行情和期权行情
  8. 增加可以处理压缩过的消息的 MdsApi_WaitOnMsgCompressible 接口, 以支持对接压缩后的行情数据

### 2. 服务端更新概要

  1. fix: 修复上海L2增量快照中最低价没有正确更新(长时间为0)的BUG
  2. fix: 修复行情订阅列表的计数器缺陷（把相同的证券代码分别作为指数代码和股票代码指定了两遍时, 会订阅不到指数行情的问题）
  3. fix: 修复没有拦截掉9:25前后已经过时的虚拟集合竞价消息的问题
  4. 修复系统缺陷, 完善管理功能和故障恢复处理


---

MDS_0.15.5.11 / 2018-06-20
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)
  2. fix: 扩大Level2增量更新消息支持的最大价位变更数量和委托明细数量, 修复在巨幅波动场景下会因为支持的价位数量不足导致丢失价位信息的BUG
     - 如果使用的是旧版本的API, 那么服务器端将不再推送增量更新消息 (只推送全量快照), 以此来保持兼容
     - 如果需要使用增量更新消息的话, 就需要更新到最新版本的API, 否则不需要更新API
  3. 行情订阅条件和订阅配置中增加 '逐笔数据的过期时间类型 tickExpireType' (兼容之前版本)

### 2. 服务端更新概要

  1. fix: 修复因行情发布服务和转发服务使用了相同的请求队列, 导致偶发行情订阅请求无法被正确处理的BUG
  2. fix: 修复在行情巨幅波动场景下因为支持的增量更新价位数量不足导致丢失价位信息的BUG
  3. fix: 修正上海L2（增量）快照会出现最新价不在最低价和最高价之间的问题
  4. fix: 避免因为把相同的证券代码分别作为指数代码和股票代码指定了两遍, 导致指数的已订阅数量为0, 进而不推送指数行情的问题
  5. 添加面向低速网络的行情转发服务
  6. 优化深证行情的转发处理, 改善早盘高峰时期行情延迟过大的问题


---

MDS_0.15.5.4 / 2018-02-22
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. fix: 解决在Windows下的兼容性问题
  3. 调整接口 MdsApi_InitAll, 增加一个函数参数 (pUdpTickOrderAddrKey), 以支持分别订阅逐笔成交和逐笔委托的行情组播
     - 因为增加了接口参数, 需要对程序进行修改, 对该参数传 NULL 即可
  4. 增加接口 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime, 用于获取通道最近接受/发送消息的时间
  5. 登录失败时, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因

### 2. 服务端更新概要

  1. fix: 优化行情推送, 改善推送服务的公平性
  2. fix: 修复在计算深圳逐笔成交的成交金额时没有转换为int64, 导致溢出的BUG
  3. fix: 修复上海L1指数快照的 securityType 不正确, 取值都是 1 的BUG
  4. fix: 修复查询L1快照时, 未按照查询条件 securityType 进行匹配的问题
  5. fix: 修复 mds_tester 查询功能无法使用的问题
  6. 支持指定行情组播发送端的端口号
  7. 优化深证行情采集, 改善早盘高峰时期行情延迟过大的问题
  8. 优化行情组播的发送延迟
