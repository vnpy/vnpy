/*
 * Copyright 2009-2016 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    oes_api.h
 *
 * Oes API库函数实现
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 增加客户信息查询功能
 *          - 补充整理错误号的注释信息和部分错误号定义
 *          - 增加 OesApi_GetErrorMsg 和 OesApi_GetErrorMsg2 方法
 *          - 在登录报文中增加协议版本号信息, 并在登录时校验协议版本号的兼容性
 * @version 0.12.1      2016/12/21
 *          - 删除 OesApi_IsBusinessError 接口, 查询接口不再返回小于 -1000 的错误
 *          - 查询接口返回值变更:
 *              - 单条查询接口无数据返回 SPK_NEG(ENOENT)
 *              - 批量查询接口无匹配数据时返回 0
 *              - 单条/批量 查询被服务器拒绝返回 SPK_NEG(EINVAL), 具体错误信息通过日志打印
 *          - 微调oes_api日志打印格式
 * @version 0.12.3      2017/01/10
 *          - 精简API依赖的头文件, 并最小化API发布包中的头文件数量
 *          - 重命名 protocol_parser/errors/oes_protocol_errors.h ==> errors/oes_errors.h
 *          - 从发布包中删除协议解析相关的头文件, 客户端如果需要的话, 可以分别发布
 *          - 单条持仓查询接口 OesApi_QuerySingleHolding 拆分:
 *              - OesApi_QuerySingleStkHolding 查询单条股票持仓
 *              - OesApi_QuerySingleOptHolding 查询单条期权持仓
 *          - OesApi_QuerySingleStkHolding 参数类型变更:
 *              - 参数四的类型变更 OesHoldItemT -> OesStkHoldingItemT(原OesStockHoldInfoT)
 *          - OesApi_QuerySingleOptHolding 参数类型变更:
 *              - 参数四的类型变更 OesHoldItemT -> OesOptHoldingItemT(原OesOptionHoldInfoT)
 *          - 批量持仓查询接口 OesApi_QueryHolding 拆分:
 *              - OesApi_QueryStkHolding 查询股票持仓
 *              - OesApi_QueryOptHolding 查询期权持仓
 *          - OesApi_QueryStkHolding 参数类型变更:
 *              - 参数二的类型变更 OesQryHoldFilterT -> OesQryStkHoldingFilterT
 *              - 参数三 pOnMsgCallback.pMsgBody 返回数据类型变更 OesHoldItemT -> OesStkHoldingItemT
 *          - OesApi_QueryOptHolding 参数类型变更:
 *              - 参数二的类型变更 OesQryHoldFilterT -> OesQryOptHoldingFilterT
 *              - 参数三 pOnMsgCallback.pMsgBody 返回数据类型变更 OesHoldItemT -> OesOptHoldingItemT
 * @version 0.12.6.3    2017/03/24
 *          - 增加oes_api.h中的头文件引用, api使用者不再需要显式引用sutil库的头文件
 * @version 0.12.8.2    2017/05/16
 *          - 新增 ‘证券发行信息查询(OesApi_QueryIssue)’ 接口, 此接口获取到的
 *            证券发行信息类型定义为 ‘OesIssueItemT’
 *          - 新增 ‘重复的认购委托(OESERR_SUBSCRIBE_ORD_DUPLICATE)’ 错误, 错误码为1240
 * @version 0.15.2      2017/07/18
 *          - 新增 ‘发送出入金委托请求(OesApi_SendFundTrsfReq)’ 接口
 *          - 新增 ‘查询新股配号、中签信息(OesApi_QueryLotWinning)’ 接口
 * @version 0.15.3      2017/08/07
 *          - 登录时oes-server端增加IP、MAC非空的校验
 * @version 0.15.3.3    2017/08/20
 *          - 新增接口 '重置线程级别的日志记录器名称 (OesApi_ResetThreadLoggerName)',
 *            以支持为当前线程设置独立的日志文件
 * @version 0.15.4      2017/08/22
 *          - 增加客户端环境号 (clEnvId), 涉及到以下函数接口、数据结构、通信报文的变更:
 *              - 以下接口函数的参数发生变更 (增加参数 clEnvId):
 *                  - 连接并登录到指定的OES节点与服务 (OesApi_Logon)
 *                  - 连接并登录到OES服务集群 (OesApi_LogonReplicaSet)
 *                  - 连接并登录到OES服务集群 (OesApi_LogonPeerNodes)
 *                  - 发送回报同步消息 (OesApi_SendReportSynchronization)
 *              - 以下通信报文发生变更 (增加字段 clEnvId):
 *                  - 登录请求/应答报文 (OesLogonReqT / OesLogonRspT)
 *              - 以下通信报文发生变更 (增加字段 subscribeEnvId):
 *                  - 回报同步请求/应答消息 (OesReportSynchronizationReqT / OesReportSynchronizationRspT)
 *              - 以下数据结构发生变更 (增加字段 clEnvId):
 *                  - 客户端会话信息/连接通道信息 (OesApiSessionInfoT)
 *                  - 远程主机配置信息 (OesApiRemoteCfgT)
 *          - 新增接口 '重置线程级别的日志记录器名称 (OesApi_ResetThreadLoggerName)',
 *            以支持为当前线程设置独立的日志文件
 *          - 重命名接口函数 OesApi_SendFundTrsfReq -> OesApi_SendFundTransferReq
 *          - 新增接口 '获取API的发行版本号 (OesApi_GetApiVersion)'
 *          - 新增接口 '获取当前交易日 (OesApi_GetTradingDay)'
 *          - 新增接口 '发送撤单请求 (OesApi_SendOrderCancelReq)'
 *              - 相比原来的撤单方式, 撤单请求接口支持通过 clEnvId + clSeqNo 进行撤单
 *          - 调整回报接口回调方法类型定义 F_OESAPI_ONMSG_T -> F_OESAPI_ON_RPT_MSG_T
 *          - 调整查询接口回调方法类型定义 F_OESAPI_ONMSG_T -> F_OESAPI_ON_QRY_MSG_T
 *          - 查询接口回调方法中增加 OesQryCursorT 类型参数, 其中携带 "是否是最后一条" 信息
 * @version 0.15.4.1    2017/09/25
 *          - 服务器端删除了对JSON等通信协议等支持, 改为只支持二进制协议
 * @version 0.15.4.2    2017/10/16
 *          - 回报同步请求处理改成异步应答模式, 回报通道增加消息类型 OESMSG_RPT_REPORT_SYNCHRONIZATION
 * @version 0.15.5      2017/11/03
 *          - 新增接口 '获取通道绑定clEnvId (OesApi_GetClEnvId)'
 * @version 0.15.5.1    2017/11/17
 *          - 增加 OesApi_IsValidOrdChannel、OesApi_IsValidRptChannel 等接口, 用于判断通道是否已经连接且有效
 * @version 0.15.5.2    2018/01/29
 *          - 增加 OesApi_GetLastRecvTime、OesApi_GetLastSendTime 接口, 用于获取通道最近发送/接收消息的时间
 *          - 登录失败时, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 * @version 0.15.5.11_u2 2018/11/04
 *          - 添加从成交回报中提取和生成委托回报信息的辅助函数
 * @version 0.15.5.14   2018/08/01
 *          - 增加 OesApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
 *          - '登录应答报文(OesLogonRspT)' 结构体中增加字段:
 *              - 客户端类型 (clientType)
 *              - 客户端状态 (clientStatus)
 *          - 增加设置当前线程登录用户名/登录密码/客户端环境号的接口
 *              - OesApi_SetThreadUsername
 *              - OesApi_SetThreadPassword
 *              - OesApi_SetThreadEnvId
 *          - 增加返回最近一次API调用失败的错误号的接口
 *              - OesApi_GetLastError
 *          - '成交查询应答报文(OesQryTrdRspT)' 和 '成交回报应答报文(OesTrdCnfmT)' 结构体中增加字段:
 *              - 证券子类型 (subSecurityType)
 * @version 0.15.5.16   2018/08/31
 *          - 增加 '获取客户端总览信息 (OesApi_GetClientOverview)' 接口
 *          - 增加 '查询主柜资金信息 (OesApi_QueryCounterCash)' 接口
 *          - 调整 '出入金委托请求 (OesApi_SendFundTransferReq)' 接口, 增加支持仅主柜和银行间的银证转账
 *          - '客户资金信息(OesCashAssetItemT)' 结构中增加字段:
 *              - 是否禁止出入金 (isFundTrsfDisabled)
 *          - '证券账户信息(OesInvAcctItemT)' 结构中增加字段:
 *              - 是否禁止交易 (isTradeDisabled)
 * @version 0.15.6      2018/08/01
 *          - 增加 OesApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
 *          - 增加修改客户端登录密码接口 (OesApi_SendChangePasswordReq)
 *          - 增加设置当前线程登录用户名/登录密码/客户端环境号的接口
 *              - OesApi_SetThreadUsername
 *              - OesApi_SetThreadPassword
 *              - OesApi_SetThreadEnvId
 *          - 增加批量委托接口 (以批量的形式同时发送多笔委托申报)
 *              - OesApi_SendBatchOrdersReq
 *              - OesApi_SendBatchOrdersReq2
 *          - 增加设置当前线程的API错误号 (OesApi_SetLastError)
 *          - 增加返回当前线程最近一次API调用失败的错误号 (OesApi_GetLastError)
 *          - 新增 ‘市场状态信息查询(OesApi_QueryMarketState)’ 接口, 此接口获取到的
 *            市场状态信息类型定义为 ‘OesMarketStateItemT’
 *          - 增加设置/获取客户端自定义的设备序列号的接口
 *              - OesApi_SetCustomizedDriverId
 *              - OesApi_GetCustomizedDriverId
 *          - 查询现货产品信息接口的过滤条件变更:
 *              - 增加 ‘证券类别(securityType)’ 条件
 *              - 增加 ‘证券子类别(subSecurityType)’ 条件
 *          - '登录应答报文(OesLogonRspT)' 结构体中增加字段:
 *              - 客户端类型 (clientType)
 *              - 客户端状态 (clientStatus)
 *          - 增加返回最近一次API调用失败的错误号的接口
 *              - OesApi_GetLastError
 *          - '成交查询应答报文(OesQryTrdRspT)' 和 '成交回报应答报文(OesTrdCnfmT)' 结构体中增加字段:
 *              - 证券子类型 (subSecurityType)
 * @version 0.15.7.4    2018/08/15
 *          - 增加 '获取客户端总览信息 (OesApi_GetClientOverview)' 接口
 *          - 增加 '查询主柜资金信息 (OesApi_QueryCounterCash)' 接口
 *          - 调整 '出入金委托请求 (OesApi_SendFundTransferReq)' 接口, 增加支持仅主柜和银行间出入金
 *          - '客户资金信息(OesCashAssetItemT)' 结构中增加字段:
 *              - 是否禁止出入金 (isFundTrsfDisabled)
 *          - '证券账户信息(OesInvAcctItemT)' 结构中增加字段:
 *              - 是否禁止交易 (isTradeDisabled)
 * @version 0.15.7.6    2018/11/03
 *          - '买卖类型(eOesBuySellTypeT)' 中新增:
 *              - 配股认购 (OES_BS_TYPE_ALLOTMENT)
 *          - 新增 '产品类型 (eOesProductTypeT)' 定义, 作为产品和持仓的高层类别定义
 *          - 在以下结构体中增加 '产品类型 (productType)' 字段
 *              - 证券信息(OesStockBaseInfoT/OesStockItemT)
 *              - 证券发行信息 (OesIssueBaseInfoT/OesIssueItemT)
 *              - 股票持仓信息 (OesStkHoldingBaseInfoT/OesStkHoldingItemT)
 *              - 委托回报 (OesOrdCnfmT/OesOrdItemT)
 *              - 成交回报 (OesTrdCnfmT/OesTrdItemT)
 *          - 查询证券发行产品信息接口(OesApi_QueryIssue)的过滤条件中增加:
 *              - ‘产品类型(productType)’ 条件
 *          - 查询股票持仓信息接口(OesApi_QueryStkHolding)的过滤条件中增加:
 *              - ‘产品类型(productType)’ 条件
 *          - '证券子类型(eOesSubSecurityTypeT)'中新增:
 *              - 沪伦通CDR本地交易业务产品(OES_SUB_SECURITY_TYPE_STOCK_HLTCDR)
 * @version 0.15.7.6_RC2 2018/11/22
 *          - 增加 OesApi_InitAllByCfgStruct 接口 (InitAll 的重载方法)
 *          - 增加 OesApi_RecvReportMsg 接口 (一次只接收一条回报消息)
 *          - 增加设置/获取当前线程订阅回报使用的客户端环境号的接口
 *              - OesApi_SetThreadSubscribeEnvId
 *              - OesApi_GetThreadSubscribeEnvId
 * @version 0.15.9_I9   2019/04/15
 *          - 重新实现登录接口 (接口OesApi_Logon)
 *              - 增强安全性处理
 * @version 0.15.9_u1   2019/06/10
 *          - 配置文件中增加配置项 driverId, 以支持通过API配置文件配置硬盘序列号
 * @version 0.15.9_u4   2019/12/03
 *          - '证券发行信息 (OesIssueItemT)' 结构中增加字段:
 *               - 停牌标识 (suspFlag)
 *               - 发行方式 (issueType)
 * @version 0.15.9.1_RC3 2019/08/02
 *          - 增加 '查询券商参数信息 (OesApi_QueryBrokerParamsInfo)' 接口
 * @version 0.15.9.4    2019/12/24
 *          - 新增 '判断错误码与错误信息条目是否匹配 (OesApi_IsErrorOf)' 接口
 *          - 新增 '判断消息头中的状态码与错误信息条目是否匹配 (OesApi_IsErrorOf2)' 接口
 *          - '现货产品基础信息 (OesStockBaseInfoT)' 结构中增加字段:
 *              - 总股本 (outstandingShare)
 *              - 流通股数量 (publicFloatShare)
 *          - '证券账户基础信息 (OesInvAcctBaseInfoT)' 结构中增加字段:
 *              - 个股持仓比例阀值(stkPositionLimitRatio)
 *          - 增加辅助的配置文件解析接口
 *              - OesApi_ParseConfigFromFile2, 解析客户端配置文件, 并可以指定是否允许配置项为空
 * @version 0.15.10.1   2020/01/17
 *          - 增加辅助的配置文件解析接口
 *              - OesApi_ParseConfigFromFile2, 解析客户端配置文件, 并可以指定是否允许配置项为空
 *          - '股票持仓基础信息 (OesStkHoldingBaseInfoT)' 结构字段变更:
 *              - 删除 当前已锁定持仓 (lockHld) 字段
 *              - 删除 当前锁定冻结持仓 (lockFrzHld) 字段
 *              - 删除 当前解锁定冻结持仓数量 (unlockFrzHld) 字段
 *              - 删除 当前备兑冻结的现货持仓数量 (coveredFrzHld) 字段
 *              - 删除 当前已备兑使用的现货持仓数量 (coveredHld) 字段
 *              - 新增 日初可用持仓 (originalAvlHld) 字段
 *              - 新增 日初锁定持仓 (originalLockHld) 字段
 *              - 新增 日中累计锁定持仓 (totalLockHld) 字段
 *              - 新增 日中累计解锁持仓 (totalUnlockHld) 字段
 *              - 新增 当日最大可减持额度 (maxReduceQuota) 字段
 *          - '客户端总览信息 (OesClientOverviewT)' 结构字段变更
 *              - 新增 客户端适用的业务范围 (businessScope) 字段
 *          - 增加异步发送密码修改请求 (仅发送请求不接收应答消息)
 *              - OesApi_SendChangePasswordReqAsynced
 *          - 为委托通道增加异步测试请求接口 (仅发送测试请求不接收应答消息)
 *              - OesApi_TestOrdChannelAsynced
 * @version 0.15.10.6   2020/05/14
 *          - 将会话信息中的发送时间(lastSendTime)和接收时间(lastRecvTime)升级为纳秒级时间戳 (STimevalT => STimespecT)
 * @version 0.15.11     2020/05/29
 *          - 增加辅助的通道组接口
 *              - OesApi_GetChannelGroupLastRecvTime, 返回通道组最近接收消息时间
 *              - OesApi_GetChannelGroupLastSendTime, 返回通道组最近发送消息时间
 *          - 增加辅助判断现货产品状态的接口
 *              - OesApi_HasStockStatus
 *          - 从现货版本中删除已经过时的期权相关查询接口定义, 包括:
 *              - 查询单条期权持仓信息 (OesApi_QuerySingleOptHolding)
 *              - 查询期权持仓信息 (OesApi_QueryOptHolding)
 *              - 查询期权产品信息 (OesApi_QueryOption)
 * @version 0.15.11.3   2020/06/29
 *          - 增加用于校验API版本号是否匹配的辅助函数
 *              - __OesApi_CheckApiVersion
 * @version 0.16.0      2019/11/20
 *          - OesApi_QuerySingleOptHolding 接口增加参数
 *              - ‘市场代码(mktId)’
 *              - ‘持仓类型(positionType)’
 *          - 新增 '查询期权标的持仓信息 OesApi_QueryOptUnderlyingHolding' 接口
 *          - '股票持仓基础信息 (OesStkHoldingBaseInfoT)' 结构字段变更:
 *              - 删除 当前已锁定持仓 (lockHld) 字段
 *              - 删除 当前锁定冻结持仓 (lockFrzHld) 字段
 *              - 删除 当前解锁定冻结持仓数量 (unlockFrzHld) 字段
 *              - 删除 当前备兑冻结的现货持仓数量 (coveredFrzHld) 字段
 *              - 删除 当前已备兑使用的现货持仓数量 (coveredHld) 字段
 *              - 新增 日初可用持仓 (originalAvlHld) 字段
 *              - 新增 日初锁定持仓 (originalLockHld) 字段
 *              - 新增 日中累计锁定持仓 (totalLockHld) 字段
 *              - 新增 日中累计解锁持仓 (totalUnlockHld) 字段
 *          - '资金变动回报和客户资金信息 (OesCashAssetItemT)' 结构字段变更:
 *              - 新增 日初持仓占用保证金 (originalMargin) 字段
 *              - 新增 行权累计待交收冻结资金 (totalExerciseFrzAmt) 字段
 *              - 新增 待追加保证金 (pendingSupplMargin) 字段
 *              - 新增 上海市场可用限购额度 (sseAvailablePurchaseLimit) 字段
 *              - 新增 深圳市场可用限购额度 (szseAvailablePurchaseLimit) 字段
 *          - '委托回报和委托信息 (OesOrdCnfmT/OesOrdItemT)' 结构字段变更:
 *              - 新增 委托当前冻结的保证金 (frzMargin) 字段
 *              - 新增 委托累计已使用的保证金 (cumMargin) 字段
 *          - '成交回报和成交信息 (OesTrdCnfmT/OesTrdItemT)' 结构字段变更:
 *              - 新增 债券利息 (trdInterest) 字段
 *              - 新增 交易费用 (trdFee) 字段
 *              - 占用/释放的保证金 (trdMargin)
 *              - 累计占用/释放的保证金 (cumMargin)
 *          - '委托状态 eOesOrdStatusT' 枚举定义调整:
 *              - 重命名 OES_ORD_STATUS_UNDEFINE => OES_ORD_STATUS_PENDING (待处理 (仅内部使用))
 *          - 新增 回报消息类型 '通知消息回报 (OESMSG_RPT_NOTIFY_INFO)'
 *          - 新增 '查询通知消息 (OesApi_QueryNotifyInfo)' 接口
 *          - 新增 回报消息类型 '期权标的持仓变动信息 (OESMSG_RPT_OPTION_UNDERLYING_HOLDING_VARIATION)'
 *          - 新增 '查询期权限仓额度信息 (OesApi_QueryOptPositionLimit)' 接口
 *          - 新增 '查询期权限购额度信息 (OesApi_QueryOptPurchaseLimit)' 接口
 *          - 新增 '查询期权行权指派信息 (OesApi_QueryOptExerciseAssign)' 接口
 *          - 新增 '查询期权结算单信息 (OesApi_QueryOptSettlementStatement)' 接口
 *          - 新增 '期权账户结算单确认 (OesApi_SendOptSettlementConfirmReq)' 接口
 * @version 0.16.0.1    2019/12/12
 *          - 新增 '上证期权业务委托类型枚举(eOesOrdTypeShOptT)' 定义
 * @version 0.16.0.2    2020/01/03
 *          - '券商参数信息 (OesBrokerParamsInfoT)' 结构字段变更:
 *              - 新增 服务端业务范围 (businessScope) 字段
 *              - 新增 期权扩展参数 (optionExt) 结构, 其中新增 投资人出金提取线 (withdrawLineRatio) 字段
 *          - 新增 '返回系统是否支持指定的业务类别 (OesApi_IsBusinessSupported)' 接口
 * @version 0.16.0.3    2020/01/17
 *          - 增加异步发送期权账户结算单确认接口 (仅发送请求不接收应答消息)
 *              - OesApi_SendOptSettlementConfirmReqAsynced
 * @version 0.16.0.4    2020/02/28
 *          - '期权标的持仓信息 (OesOptUnderlyingHoldingItemT)' 结构字段变更:
 *              - 新增 当日最大可减持额度 (maxReduceQuota) 字段
 *          - '资金变动回报 (OesCashAssetReportT)' 和 '客户资金信息 (OesCashAssetItemT)' 结构字段变更:
 *              - 新增 未对冲实时价格保证金 (totalMarketMargin) 字段
 *              - 新增 已对冲实时价格保证金 (totalNetMargin) 字段
 *
 * @since   2016/03/04
 */


#ifndef _OES_API_H
#define _OES_API_H


#include    <oes_global/oes_base_model.h>
#include    <oes_global/oes_packets.h>
#include    <oes_api/errors/oes_errors.h>
#include    <sutil/net/spk_general_client_define.h>
#include    <sutil/platform/spk_platforms.h>

/* 为了方便外部使用而额外引入的头文件 *
#include    <sutil/time/spk_times.h>
#include    <sutil/logger/spk_log.h>
*/


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 默认的主配置区段名称 */
#define OESAPI_CFG_DEFAULT_SECTION              "oes_client"
/** 默认的日志配置区段名称 */
#define OESAPI_CFG_DEFAULT_SECTION_LOGGER       "log"

/** 默认的委托申报配置项名称 */
#define OESAPI_CFG_DEFAULT_KEY_ORD_ADDR         "ordServer"
/** 默认的执行报告配置项名称 */
#define OESAPI_CFG_DEFAULT_KEY_RPT_ADDR         "rptServer"
/** 默认的查询服务配置项名称 */
#define OESAPI_CFG_DEFAULT_KEY_QRY_ADDR         "qryServer"
/** 默认的消息类型列表等字符串分隔符 */
#define OESAPI_DEFAULT_STRING_DELIM             ",;| \t\r\n"
/* -------------------------           */


/* ===================================================================
 * 常量定义, 枚举类型定义
 * =================================================================== */

/**
 * 通道类型定义
 */
typedef enum _eOesApiChannelType {
    OESAPI_CHANNEL_TYPE_ORDER       = 1,        /**< 委托申报通道 */
    OESAPI_CHANNEL_TYPE_REPORT      = 2,        /**< 回报通道 */
    OESAPI_CHANNEL_TYPE_QUERY       = 3         /**< 查询通道 */
} eOesApiChannelTypeT;
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * 客户端会话信息 (连接通道信息) 定义
 */
typedef SGeneralClientChannelT      OesApiSessionInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_SESSION_INFO             \
        NULLOBJ_GENERAL_CLIENT_CHANNEL
/* -------------------------           */


/**
 * 客户端会话的连接通道组定义 (多个连接通道的集合)
 */
typedef SGeneralClientChannelGroupT OesApiChannelGroupT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_CHANNEL_GROUP            \
        NULLOBJ_GENERAL_CLIENT_CHANNEL_GROUP
/* -------------------------           */


/**
 * Socket URI地址信息
 */
typedef SGeneralClientAddrInfoT     OesApiAddrInfoT;


/* 结构体初始化值定义 */
#define NULLOBJ_OESAPI_ADDR_INFO                \
        NULLOBJ_GENERAL_CLIENT_ADDR_INFO
/* -------------------------           */


/**
 * 远程主机配置信息
 */
typedef SGeneralClientRemoteCfgT    OesApiRemoteCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_REMOTE_CFG               \
        NULLOBJ_GENERAL_CLIENT_REMOTE_CFG
/* -------------------------           */


/**
 * 主机地址列表的游标信息
 */
typedef SGeneralClientAddrCursorT   OesApiAddrCursorT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_ADDR_CURSOR              \
        NULLOBJ_GENERAL_CLIENT_ADDR_CURSOR
/* -------------------------           */


/**
 * 回报订阅的订阅参数信息
 */
typedef struct _OesApiSubscribeInfo {
    /**
     * 待订阅的客户端环境号
     * - 大于0, 区分环境号, 仅订阅环境号对应的回报数据
     * - 小于等于0, 不区分环境号, 订阅该客户下的所有回报数据
     */
    int8                    clEnvId;

    /** 按64位对齐的填充域 */
    uint8                   __filler[3];

    /**
     * 待订阅的回报消息种类
     * - 0:      默认回报 (等价于: 0x01,0x02,0x04,0x08,0x10,0x20,0x40)
     * - 0x0001: OES业务拒绝 (未通过风控检查等)
     * - 0x0002: OES委托已生成 (已通过风控检查)
     * - 0x0004: 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知)
     * - 0x0008: 交易所成交回报
     * - 0x0010: 出入金委托执行报告 (包括出入金委托拒绝、出入金委托回报)
     * - 0x0020: 资金变动信息
     * - 0x0040: 持仓变动信息
     * - 0x0080: 市场状态信息
     * - 0x0100: 通知消息回报
     * - 0xFFFF: 所有回报
     *
     * @see eOesSubscribeReportTypeT
     */
    int32                   rptTypes;
} OesApiSubscribeInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_SUBSCRIBE_INFO           \
        0, {0}, 0
/* -------------------------           */


/**
 * 完整的OES客户端配置信息
 */
typedef struct _OesApiClientCfg {
    OesApiRemoteCfgT        ordChannelCfg;      /**< 委托服务配置 */
    OesApiRemoteCfgT        rptChannelCfg;      /**< 回报服务配置 */
    OesApiRemoteCfgT        qryChannelCfg;      /**< 查询服务配置 */
    OesApiSubscribeInfoT    subscribeInfo;      /**< 回报订阅参数 */
} OesApiClientCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_CLIENT_CFG               \
        {NULLOBJ_OESAPI_REMOTE_CFG}, \
        {NULLOBJ_OESAPI_REMOTE_CFG}, \
        {NULLOBJ_OESAPI_REMOTE_CFG}, \
        {NULLOBJ_OESAPI_SUBSCRIBE_INFO}
/* -------------------------           */


/**
 * OES客户端运行时环境
 */
typedef struct _OesApiClientEnv {
    OesApiSessionInfoT      ordChannel;         /**< 委托通道的会话信息 */
    OesApiSessionInfoT      rptChannel;         /**< 回报通道的会话信息 */
    OesApiSessionInfoT      qryChannel;         /**< 查询通道的会话信息 */
} OesApiClientEnvT;


/* 结构体初始化值定义 */
#define NULLOBJ_OESAPI_CLIENT_ENV               \
        {NULLOBJ_OESAPI_SESSION_INFO}, \
        {NULLOBJ_OESAPI_SESSION_INFO}, \
        {NULLOBJ_OESAPI_SESSION_INFO}
/* -------------------------           */


/* ===================================================================
 * 回调函数的函数原型定义
 * =================================================================== */

/**
 * 回报消息处理对应的回调函数的函数原型定义
 *
 * @param   pSessionInfo        会话信息
 * @param   pMsgHead            消息头
 * @param   pMsgBody            消息体数据
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 成功
 * @retval  <0                  小于0, 处理失败 (负的错误号)
 *
 * @see     eOesMsgTypeT
 * @see     OesRspMsgBodyT
 * @see     OesRptMsgT
 */
typedef int32   (*F_OESAPI_ON_RPT_MSG_T) (
                OesApiSessionInfoT *pSessionInfo,
                SMsgHeadT *pMsgHead,
                void *pMsgBody,
                void *pCallbackParams);
/* -------------------------           */


/**
 * 查询消息处理对应的回调函数的函数原型定义
 *
 * @param   pSessionInfo        会话信息
 * @param   pMsgHead            消息头
 * @param   pMsgBody            消息体数据
 * @param   pQryCursor          指示查询进度的游标
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 成功
 * @retval  <0                  小于0, 处理失败 (负的错误号)
 *
 * @see     eOesMsgTypeT
 * @see     OesQryRspMsgT
 */
typedef int32   (*F_OESAPI_ON_QRY_MSG_T) (
                OesApiSessionInfoT *pSessionInfo,
                SMsgHeadT *pMsgHead,
                void *pMsgBody,
                OesQryCursorT *pQryCursor,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 委托申报接口
 * =================================================================== */

/**
 * 发送委托申报请求
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中, "客户委托流水号" 是由客户端维护的线性递增序列, 用于标识委托数据的
 *     唯一性, 并防止重复申报
 *   - 从0.11版本开始, 不再强制要求线性递增, 只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *   - 当通过撤单请求接口进行撤单时, 可以直接通过待撤订单的 "客户委托流水号(clSeqNo)" 进行撤单
 *   - 此外, 当需要同时建立多个委托通道报单时, 可以通过 "客户端环境号(clEnvId)" 对区分不同的
 *     委托通道, "客户委托流水号(clSeqNo)" 只要在相同的 "客户端环境号(clEnvId)" 下唯一即可
 *
 * - 关于"原始订单的客户订单编号(origClOrdId)"
 *   - "客户订单编号(clOrdId)", 是由OES服务器端维护的、在OES内具有唯一性的内部委托编号,
 *     该编号会通过回报数据返回客户端
 *   - 当通过撤单请求接口进行撤单时, 可以通过待撤订单的 "客户委托流水号(clSeqNo)" 或者
 *     "客户订单编号(clOrdId)" 进行撤单
 *
 * @param       pOrdChannel     委托通道的会话信息
 * @param       pOrdReq         待发送的委托申报请求
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendOrderReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOrdReqT *pOrdReq);

/**
 * 发送撤单请求
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中, "客户委托流水号" 是由客户端维护的线性递增序列, 用于标识委托数据的
 *     唯一性, 并防止重复申报
 *   - 从0.11版本开始, 不再强制要求线性递增, 只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *   - 当通过撤单请求接口进行撤单时, 可以直接通过待撤订单的 "客户委托流水号(clSeqNo)" 进行撤单
 *   - 此外, 当需要同时建立多个委托通道报单时, 可以通过 "客户端环境号(clEnvId)" 对区分不同的
 *     委托通道, "客户委托流水号(clSeqNo)" 只要在相同的 "客户端环境号(clEnvId)" 下唯一即可
 *
 * - 关于"原始订单的客户订单编号(origClOrdId)"
 *   - "客户订单编号(clOrdId)", 是由OES服务器端维护的、在OES内具有唯一性的内部委托编号,
 *     该编号会通过回报数据返回客户端
 *   - 当通过撤单请求接口进行撤单时, 可以通过待撤订单的 "客户委托流水号(clSeqNo)" 或者
 *     "客户订单编号(clOrdId)" 进行撤单
 *
 * @param       pOrdChannel     查询通道的会话信息
 * @param       pCancelReq      待发送的撤单请求
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendOrderCancelReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOrdCancelReqT *pCancelReq);

/**
 * 批量发送多条委托请求
 * 以批量的形式同时发送多笔委托申报, 而风控检查等处理结果则仍以单笔委托为单位通过回报数据返回
 *
 * - 批量委托的委托请求填充规则与单条委托完全相同, 回报处理规则也与单条委托完全相同:
 *   - 每笔委托请求的 "客户委托流水号(clSeqNo)" 同样必须填充, 并需要维持在同一客户端下的唯一性
 *   - 服务器端的处理结果则仍将以单笔委托为单位通过回报数据返回
 *
 * @param       pOrdChannel     委托通道的会话信息
 * @param       ppOrdPtrList    待发送的委托请求列表 (指针数组)
 * @param       ordCount        待发送的委托请求数量
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendBatchOrdersReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOrdReqT *ppOrdPtrList[],
                int32 ordCount);

/**
 * 批量发送多条委托请求
 * 以批量的形式同时发送多笔委托申报, 而风控检查等处理结果则仍以单笔委托为单位通过回报数据返回
 *
 * - 批量委托的委托请求填充规则与单条委托完全相同, 回报处理规则也与单条委托完全相同:
 *   - 每笔委托请求的 "客户委托流水号(clSeqNo)" 同样必须填充, 并需要维持在同一客户端下的唯一性
 *   - 服务器端的处理结果则仍将以单笔委托为单位通过回报数据返回
 *
 * @param       pOrdChannel     委托通道的会话信息
 * @param       pOrdReqArray    待发送的委托请求数组 (连续的存储空间)
 * @param       ordCount        待发送的委托请求数量
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendBatchOrdersReq2(
                OesApiSessionInfoT *pOrdChannel,
                OesOrdReqT *pOrdReqArray,
                int32 ordCount);

/**
 * 发送出入金委托请求
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中, "客户委托流水号" 是由客户端维护的线性递增序列, 用于标识委托数据的
 *     唯一性, 并防止重复申报
 *   - 从0.11版本开始, 不再强制要求线性递增, 只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *
 * @param       pOrdChannel     委托通道的会话信息
 * @param       pFundTrsfReq    待发送的出入金委托请求
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendFundTransferReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesFundTrsfReqT *pFundTrsfReq);

/**
 * 发送密码修改请求 (修改客户端登录密码)
 * 密码修改请求将通过委托通道发送到OES服务器, 并将采用同步请求/应答的方式直接返回处理结果
 *
 * @param       pOrdChannel     委托通道会话信息
 * @param[in]   pChangePasswordReq
 *                              待发送的密码修改请求
 * @param[out]  pOutChangePasswordRsp
 *                              用于输出密码修改请求应答的缓存区
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (OES错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendChangePasswordReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesChangePasswordReqT *pChangePasswordReq,
                OesChangePasswordRspT *pOutChangePasswordRsp);

/**
 * 异步发送密码修改请求 (仅发送请求不接收应答消息)
 *
 * @param       pOrdChannel     委托通道会话信息
 * @param[in]   pChangePasswordReq
 *                              待发送的密码修改请求
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (异步接口不会返回>0的值)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendChangePasswordReqAsynced(
                OesApiSessionInfoT *pOrdChannel,
                const OesChangePasswordReqT *pChangePasswordReq);
/* -------------------------           */


/* ===================================================================
 * 期权业务特有的委托接口
 * =================================================================== */

/**
 * 期权账户结算单确认
 * 结算单确认请求将通过委托通道发送到OES服务器, 并将采用同步请求/应答的方式直接返回处理结果
 *
 * @note 结算单确认后, 方可进行委托申报和出入金请求
 *
 * @param       pOrdChannel     委托通道会话信息
 * @param[in]   pOptSettlementConfirmReq
 *                              待发送的结算单确认请求
 *                              - 客户端仅关联一个客户时, 可传空指针或不指定客户代码
 * @param[out]  pOptSettlementConfirmRsp
 *                              用于输出结算单确认请求应答的缓存区
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (OES错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendOptSettlementConfirmReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOptSettlementConfirmReqT *pOptSettlementConfirmReq,
                OesOptSettlementConfirmRspT *pOptSettlementConfirmRsp);

/**
 * 异步发送期权账户结算单确认 (仅发送请求不接收应答消息)
 *
 * @note 结算单确认后, 方可进行委托申报和出入金请求
 *
 * @param       pOrdChannel     委托通道会话信息
 * @param[in]   pOptSettlementConfirmReq
 *                              待发送的结算单确认请求
 *                              - 客户端仅关联一个客户时, 可传空指针或不指定客户代码
 * @param[out]  pOptSettlementConfirmRsp
 *                              用于输出结算单确认请求应答的缓存区
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (OES错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesApi_SendOptSettlementConfirmReqAsynced(
                OesApiSessionInfoT *pOrdChannel,
                const OesOptSettlementConfirmReqT *pOptSettlementConfirmReq,
                OesOptSettlementConfirmRspT *pOptSettlementConfirmRsp);
/* -------------------------           */


/* ===================================================================
 * 执行报告接口
 * =================================================================== */

/**
 * 等待回报消息到达, 并通过回调函数进行消息处理
 *
 * @param       pRptChannel     会话信息
 * @param       timeoutMs       超时时间(毫秒)
 * @param       pRptMsgCallback 进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesRptMsgT</code>
 * @param       pCallbackParams 回调函数的参数
 * @retval      >=0             成功 (返回回调函数的返回值)
 * @retval      <0              失败 (负的错误号)
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由read()系统调用或回调函数pOnMsgCallback返回的错误
 *
 * @see         OesRptMsgT
 * @see         eOesMsgTypeT
 * @see         F_OESAPI_ON_RPT_MSG_T
 */
int32   OesApi_WaitReportMsg(
                OesApiSessionInfoT *pRptChannel,
                int32 timeoutMs,
                F_OESAPI_ON_RPT_MSG_T pRptMsgCallback,
                void *pCallbackParams);

/**
 * 接收(一条)回报消息
 * 阻塞等待直到完整的接收到一条回报消息或者到达超时时间
 *
 * @param       pRptChannel     会话信息
 * @param[out]  pOutMsgHead     消息头缓存
 * @param[out]  pOutMsgBody     消息体数据缓存
 * @param       bufSize         消息体数据缓存区的大小
 * @param       timeoutMs       超时时间(毫秒)
 * @return      大于等于0, 消息体数据长度; 小于0, 错误号
 */
int32   OesApi_RecvReportMsg(
                OesApiSessionInfoT *pRptChannel,
                SMsgHeadT *pOutMsgHead,
                OesRspMsgBodyT *pOutMsgBody,
                int32 bufSize,
                int32 timeoutMs);
/* -------------------------           */


/* ===================================================================
 * 查询接口
 * =================================================================== */

/**
 * 获取API的发行版本号
 *
 * @retval  API的发行版本号 (如: "0.15.3")
 */
const char *
        OesApi_GetApiVersion();

/**
 * 获取当前交易日
 *
 * @param   pQryChannel         查询通道的会话信息
 * @retval  >=0                 当前交易日 (格式：YYYYMMDD)
 * @retval  <0                  失败 (负的错误号)
 */
int32   OesApi_GetTradingDay(
                OesApiSessionInfoT *pQryChannel);

/**
 * 获取客户端总览信息
 *
 * @param       pQryChannel         查询通道的会话信息
 * @param[out]  pOutClientOverview  查询到的客户端总览信息
 * @retval      =0                  查询成功
 * @retval      <0                  失败 (负的错误号)
 */
int32   OesApi_GetClientOverview(
                OesApiSessionInfoT *pQryChannel,
                OesClientOverviewT *pOutClientOverview);

/**
 * 查询单条委托信息
 *
 * @param       pQryChannel     查询通道的会话信息
 * @param       clSeqNo         委托流水号
 * @param[out]  pOutOrdItem     查询到的委托信息
 * @retval      =0              查询成功
 * @retval      <0              查询失败 (负的错误号)
 *
 * @see         OesOrdItemT
 */
int32   OesApi_QuerySingleOrder(
                OesApiSessionInfoT *pQryChannel,
                int32 clSeqNo,
                OesOrdItemT *pOutOrdItem);

/**
 * 查询单条资金信息
 *
 * @param       pQryChannel         查询通道的会话信息
 * @param       pCashAcctId         资金账号
 * @param[out]  pOutCashAssetItem   查询到的资金信息
 * @retval      =0                  查询成功
 * @retval      <0                  查询失败 (负的错误号)
 *
 * @see         OesCashAssetItemT
 */
int32   OesApi_QuerySingleCashAsset(
                OesApiSessionInfoT *pQryChannel,
                const char *pCashAcctId,
                OesCashAssetItemT *pOutCashAssetItem);

/**
 * 查询单条股票持仓信息
 *
 * @param       pQryChannel         查询通道的会话信息
 * @param       pInvAcctId          股东账号
 * @param       pSecurityId         证券代码
 * @param[out]  pOutHoldingItem     查询到的持仓信息
 * @retval      =0                  查询成功
 * @retval      <0                  查询失败 (负的错误号)
 *
 * @see         OesStkHoldingItemT
 */
int32   OesApi_QuerySingleStkHolding(
                OesApiSessionInfoT *pQryChannel,
                const char *pInvAcctId,
                const char *pSecurityId,
                OesStkHoldingItemT *pOutHoldingItem);

/**
 * 查询所有委托信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOrdItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOrdItemT
 */
int32   OesApi_QueryOrder(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOrdFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询成交信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesTrdItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesTrdItemT
 */
int32   OesApi_QueryTrade(
                OesApiSessionInfoT *pQryChannel,
                const OesQryTrdFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询客户资金信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesCashAssetItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesCashAssetItemT
 */
int32   OesApi_QueryCashAsset(
                OesApiSessionInfoT *pQryChannel,
                const OesQryCashAssetFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询股票持仓信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesStkHoldingItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesStkHoldingItemT
 */
int32   OesApi_QueryStkHolding(
                OesApiSessionInfoT *pQryChannel,
                const OesQryStkHoldingFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询新股配号、中签信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesLotWinningItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesLotWinningItemT
 */
int32   OesApi_QueryLotWinning(
                OesApiSessionInfoT *pQryChannel,
                const OesQryLotWinningFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询客户信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesCustItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesCustItemT
 */
int32   OesApi_QueryCustInfo(
                OesApiSessionInfoT *pQryChannel,
                const OesQryCustFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询证券账户信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesInvAcctItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesInvAcctItemT
 */
int32   OesApi_QueryInvAcct(
                OesApiSessionInfoT *pQryChannel,
                const OesQryInvAcctFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询佣金信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesCommissionRateItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesCommissionRateItemT
 */
int32   OesApi_QueryCommissionRate(
                OesApiSessionInfoT *pQryChannel,
                const OesQryCommissionRateFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询出入金流水
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesFundTransferSerialItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesFundTransferSerialItemT
 */
int32   OesApi_QueryFundTransferSerial(
                OesApiSessionInfoT *pQryChannel,
                const OesQryFundTransferSerialFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询证券发行产品信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesIssueItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesIssueItemT
 */
int32   OesApi_QueryIssue(
                OesApiSessionInfoT *pQryChannel,
                const OesQryIssueFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询现货产品信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesStockItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesStockItemT
 */
int32   OesApi_QueryStock(
                OesApiSessionInfoT *pQryChannel,
                const OesQryStockFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询ETF申赎产品信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 实际的消息体数据类型为 <code>OesEtfItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesEtfItemT
 */
int32   OesApi_QueryEtf(
                OesApiSessionInfoT *pQryChannel,
                const OesQryEtfFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询ETF成份证券信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 过滤条件中fundId参数必填
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesEtfComponentItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesEtfComponentItemT
 */
int32   OesApi_QueryEtfComponent(
                OesApiSessionInfoT *pQryChannel,
                const OesQryEtfComponentFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询市场状态信息
 *
 * @note    目前仅深圳交易所各个交易平台的市场状态信息有效
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesMarketStateItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesMarketStateItemT
 */
int32   OesApi_QueryMarketState(
                OesApiSessionInfoT *pQryChannel,
                const OesQryMarketStateFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);


/**
 * 查询通知消息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesNotifyInfoItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesNotifyInfoItemT
 */
int32   OesApi_QueryNotifyInfo(
                OesApiSessionInfoT *pQryChannel,
                const OesQryNotifyInfoFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);


/**
 * 查询主柜资金信息
 *
 * @param       pQryChannel     查询通道的会话信息
 * @param       pCashAcctId     资金账号
 * @param[out]  pOutCounterCashItem
 *                              查询到的主柜资金信息
 * @retval      =0              查询成功
 * @retval      <0              查询失败 (负的错误号)
 *
 * @see         OesCounterCashItemT
 */
int32   OesApi_QueryCounterCash(
                OesApiSessionInfoT *pQryChannel,
                const char *pCashAcctId,
                OesCounterCashItemT *pOutCounterCashItem);


/**
 * 查询券商参数信息
 *
 * @param       pQryChannel     查询通道的会话信息
 * @param[out]  pOutBrokerParams
 *                              查询到的券商参数信息
 * @retval      =0              查询成功
 * @retval      <0              查询失败 (负的错误号)
 *
 * @see         OesBrokerParamsInfoT
 */
int32   OesApi_QueryBrokerParamsInfo(
                OesApiSessionInfoT *pQryChannel,
                OesBrokerParamsInfoT *pOutBrokerParams);
/* -------------------------           */


/* ===================================================================
 * 期权业务特有的查询接口
 * =================================================================== */

/**
 * 查询期权产品信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0，将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOptionItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOptionItemT
 */
int32   OesApi_QueryOption(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptionFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询单条期权持仓信息
 *
 * @param       pQryChannel         查询通道的会话信息
 * @param       pInvAcctId          股东账号
 * @param       pSecurityId         证券代码
 * @param       mktId               市场代码
 * @param       positionType        持仓类型
 * @param[out]  pOutHoldingItem     查询到的持仓信息
 * @retval      =0                  查询成功
 * @retval      <0                  查询失败 (负的错误号)
 *
 * @see         OesOptHoldingItemT
 */
int32   OesApi_QuerySingleOptHolding(
                OesApiSessionInfoT *pQryChannel,
                const char *pInvAcctId,
                const char *pSecurityId,
                uint8 mktId,
                uint8 positionType,
                OesOptHoldingItemT *pOutHoldingItem);

/**
 * 查询期权持仓信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0，将查询当前客户下所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOptHoldingItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOptHoldingItemT
 */
int32   OesApi_QueryOptHolding(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptHoldingFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询期权标的持仓信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询条件过滤条件
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOptUnderlyingHoldingItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOptUnderlyingHoldingItemT
 */
int32   OesApi_QueryOptUnderlyingHolding(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptUnderlyingHoldingFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);


/**
 * 查询期权限购额度信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询条件过滤条件
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOptPositionLimitItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOptPositionLimitItemT
 */
int32   OesApi_QueryOptPositionLimit(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptPositionLimitFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);


/**
 * 查询期权限购额度信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0，将查询所有数据
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOptPurchaseLimitItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOptPurchaseLimitItemT
 */
int32   OesApi_QueryOptPurchaseLimit(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptPurchaseLimitFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);


/**
 * 查询期权行权指派信息
 *
 * @param   pQryChannel         查询通道的会话信息
 * @param   pQryFilter          查询条件过滤条件
 * @param   pQryMsgCallback     进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>OesOptExerciseAssignItemT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     OesOptExerciseAssignItemT
 */
int32   OesApi_QueryOptExerciseAssign(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptExerciseAssignFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);


/**
 * 查询期权结算单信息
 *
 * @param       pQryChannel         查询通道的会话信息
 * @param       pCustId             客户代码
 * @param[out]  pOutSettlementInfo  用于输出结算单信息的缓存区
 * @param       settlementInfoSize  结算单缓存区大小
 * @retval      >=0                 返回的结算单信息的实际长度
 * @retval      <0                  失败 (负的错误号)
 *
 */
int32   OesApi_QueryOptSettlementStatement(
                OesApiSessionInfoT *pQryChannel,
                const char *pCustId,
                char *pOutSettlementInfo,
                int32 settlementInfoSize);
/* -------------------------           */


/* ===================================================================
 * 基础的会话管理函数声明
 * =================================================================== */

/**
 * 连接并登录到指定的OES节点与服务
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中, "客户委托流水号" 是由客户端维护的线性递增序列, 用于标识委托数据的
 *     唯一性, 并防止重复申报
 *   - 从0.11版本开始, 不再强制要求线性递增, 只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       channelType     通道类型
 * @param       pUri            URI地址 (e.g. tcp://127.0.0.1:5100)
 * @param       pUsername       用户名
 * @param       pPassword       密码
 * @param       clEnvId         客户端环境号
 *                              - 取值范围为[0~99], [100~127]为保留区间, 客户端应避免使用
 *                              - 小于0表示不指定, 将使用配置文件或线程私有变量中设置的值
 * @param       heartBtInt      心跳间隔,单位为秒
 * @param       pSocketOptions  套接字参数 (为空, 则会使用默认参数)
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_Logon(
                OesApiSessionInfoT *pOutSessionInfo,
                eOesApiChannelTypeT channelType,
                const char *pUri,
                const char *pUsername,
                const char *pPassword,
                int8 clEnvId,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 连接并登录到OES服务集群 (基于复制集的高可用集群)
 *
 * - 关于地址列表:
 *   - 待解析的地址列表可是以空格、逗号或分号分割的地址列表字符串
 *     - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 *   - 同时也可以在每个地址之前, 为其指定对应的主机编号
 *     - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *             3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       channelType     通道类型
 * @param       pUriList        主机地址列表 (以空格、逗号或分号分割的地址列表字符串)
 * @param       pUsername       用户名
 * @param       pPassword       密码
 * @param       clEnvId         客户端环境号
 *                              - 取值范围为[0~99], [100~127]为保留区间, 客户端应避免使用
 *                              - 小于0表示不指定, 将使用配置文件或线程私有变量中设置的值
 * @param       heartBtInt      心跳间隔,单位为秒
 * @param       pSocketOptions  套接字参数 (为空, 则会使用默认参数)
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_LogonReplicaSet(
                OesApiSessionInfoT *pOutSessionInfo,
                eOesApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int8 clEnvId,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 连接并登录到OES服务集群 (基于对等节点的服务集群)
 *
 * - 关于地址列表:
 *   - 待解析的地址列表可是以空格、逗号或分号分割的地址列表字符串
 *     - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 *   - 同时也可以在每个地址之前, 为其指定对应的主机编号
 *     - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *             3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       channelType     通道类型
 * @param       pUriList        主机地址列表 (以空格、逗号或分号分割的地址列表字符串)
 * @param       pUsername       用户名
 * @param       pPassword       密码
 * @param       clEnvId         客户端环境号
 *                              - 取值范围为[0~99], [100~127]为保留区间, 客户端应避免使用
 *                              - 小于0表示不指定, 将使用配置文件或线程私有变量中设置的值
 * @param       heartBtInt      心跳间隔,单位为秒
 * @param       pSocketOptions  套接字参数 (为空, 则会使用默认参数)
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_LogonPeerNodes(
                OesApiSessionInfoT *pOutSessionInfo,
                eOesApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int8 clEnvId,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 发送回报同步消息
 *
 * @param   pRptChannel         会话信息
 * @param   subscribeEnvId      待订阅的客户端环境号
 *                              - 大于0, 区分环境号, 仅订阅环境号对应的回报数据
 *                              - 小于等于0, 不区分环境号, 订阅该客户下的所有回报数据
 * @param   subscribeRptTypes   待订阅的回报消息种类 (e.g.
 *                              OES_SUB_RPT_TYPE_ORDER_INSERT
 *                              | OES_SUB_RPT_TYPE_ORDER_REPORT
 *                              | OES_SUB_RPT_TYPE_TRADE_REPORT)
 *                              @see eOesSubscribeReportTypeT
 * @param   lastRptSeqNum       客户端最后接收到的回报数据的回报编号
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 从指定的回报编号开始推送回报数据
 *                              - 小于0, 从最新的数据开始推送回报数据
 * @return  TRUE 成功; FALSE 失败
 * @note    如果没有收到该消息, OES不会向客户端发送回报数据
 */
BOOL    OesApi_SendReportSynchronization(
                OesApiSessionInfoT *pRptChannel,
                int8 subscribeEnvId,
                int32 subscribeRptTypes,
                int64 lastRptSeqNum);

/**
 * 发送心跳消息
 *
 * @param   pSessionInfo        会话信息
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_SendHeartbeat(
                OesApiSessionInfoT *pSessionInfo);

/**
 * 发送委托通道的测试请求消息
 * 委托通道的测试请求消息为同步的请求/应答消息
 *
 * @param   pOrdChannel         委托通道会话信息
 * @param   pTestReqId          测试请求标识符 (C32, 可以为空)
 * @param   testReqIdSize       测试请求标识符的长度
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_TestOrdChannel(
                OesApiSessionInfoT *pOrdChannel,
                const char *pTestReqId,
                int32 testReqIdSize);

/**
 * 发送委托通道的测试请求消息
 * 委托通道的测试请求消息为同步的请求/应答消息
 *
 * @param       pOrdChannel     委托通道会话信息
 * @param[in]   pTestReq        待发送的测试请求
 * @param[out]  pOutTestRsp     用于输出测试请求应答的缓存区
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesApi_TestOrdChannel2(
                OesApiSessionInfoT *pOrdChannel,
                OesTestRequestReqT *pTestReq,
                OesTestRequestRspT *pOutTestRsp);

/**
 * 发送委托通道的异步测试请求消息 (仅发送测试请求不接收应答消息)
 *
 * @param   pOrdChannel         委托通道会话信息
 * @param   pTestReqId          测试请求标识符 (C32, 可以为空)
 * @param   testReqIdSize       测试请求标识符的长度
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_TestOrdChannelAsynced(
                OesApiSessionInfoT *pOrdChannel,
                const char *pTestReqId,
                int32 testReqIdSize);

/**
 * 发送回报通道的测试请求消息
 * 回报通道的测试请求消息为异步的请求/应答消息
 *
 * @param   pRptChannel         回报通道会话信息
 * @param   pTestReqId          测试请求标识符 (C32, 可以为空)
 * @param   testReqIdSize       测试请求标识符的长度
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_TestRptChannel(
                OesApiSessionInfoT *pRptChannel,
                const char *pTestReqId,
                int32 testReqIdSize);

/**
 * 发送回报通道的测试请求消息
 * 回报通道的测试请求消息为异步的请求/应答消息
 *
 * @param       pRptChannel     回报通道会话信息
 * @param[in]   pTestReq        待发送的测试请求
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesApi_TestRptChannel2(
                OesApiSessionInfoT *pRptChannel,
                OesTestRequestReqT *pTestReq);

/**
 * 发送注销消息
 *
 * @param   pSessionInfo        会话信息
 * @param   isDestory           发送注销消息后是否立即释放相关资源
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_Logout(
                OesApiSessionInfoT *pSessionInfo,
                BOOL isDestory);

/**
 * 直接断开与服务器的连接并释放会话数据
 *
 * @param   pSessionInfo        会话信息
 */
void    OesApi_Destory(
                OesApiSessionInfoT *pSessionInfo);
/* -------------------------           */


/* ===================================================================
 * 完整的客户端环境初始化与析构接口声明
 * =================================================================== */

/**
 * 完整的初始化客户端环境
 *
 * @param[out]  pOutCliEnv      输出客户端环境信息
 * @param       pCfgFile        配置文件路径
 * @param       pLoggerSection  日志记录器的配置区段名称
 * @param       pCfgSection     客户端配置区段名称
 * @param       pOrdAddrKey     委托申报服务地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pRptAddrKey     执行报告回报服务地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pQryAddrKey     查询服务地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       lastRptSeqNum   客户端最后接收到的回报数据的"回报编号(rptSeqNum)"
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *                              - 小于0, 从最新的数据开始推送回报数据
 *                              - 回报编号参见 @see OesRptMsgHeadT.rptSeqNum
 * @param[out]  pOutLastClSeqNo 返回服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 *                              - NULL表示忽略该参数
 *                              - "客户委托流水号" 是由客户端自行维护的委托流水, 用于标识
 *                                委托数据的唯一性, 并防止重复申报
 *                              - "客户委托流水号" 的取值范围没有限制, 只要维持在同一客户
 *                                端的同一个环境号(clEnvId)下的唯一即可
 *                              - 建议使用递增的正整数序列作为 "客户委托流水号" 的取值范围
 *                              - 客户委托流水号参见 @see OesOrdReqT.clSeqNo
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 *
 * @see         OesApi_InitAllByConvention
 * @see         OesApi_InitAllByCfgStruct
 */
BOOL    OesApi_InitAll(
                OesApiClientEnvT *pOutCliEnv,
                const char *pCfgFile,
                const char *pLoggerSection,
                const char *pCfgSection,
                const char *pOrdAddrKey,
                const char *pRptAddrKey,
                const char *pQryAddrKey,
                int64 lastRptSeqNum,
                int32 *pOutLastClSeqNo);

/**
 * 按照默认的配置名称, 完整的初始化客户端环境
 *
 * 等价于下面的代码:
 * <code>
 *  return OesApi_InitAll(pOutCliEnv, pCfgFile,
 *         OESAPI_CFG_DEFAULT_SECTION_LOGGER, OESAPI_CFG_DEFAULT_SECTION,
 *         OESAPI_CFG_DEFAULT_KEY_ORD_ADDR, OESAPI_CFG_DEFAULT_KEY_RPT_ADDR,
 *         OESAPI_CFG_DEFAULT_KEY_QRY_ADDR, lastRptSeqNum, pLastClSeqNo);
 * </code>
 *
 * @param[out]  pOutCliEnv      输出客户端环境信息
 * @param       pCfgFile        配置文件路径
 * @param       lastRptSeqNum   客户端最后接收到的回报数据的"回报编号(rptSeqNum)"
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *                              - 小于0, 从最新的数据开始推送回报数据
 *                              - 回报编号参见 @see OesRptMsgHeadT.rptSeqNum
 * @param[out]  pOutLastClSeqNo 返回服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 *                              - NULL表示忽略该参数
 *                              - "客户委托流水号" 是由客户端自行维护的委托流水, 用于标识
 *                                委托数据的唯一性, 并防止重复申报
 *                              - "客户委托流水号" 的取值范围没有限制, 只要维持在同一客户
 *                                端的同一个环境号(clEnvId)下的唯一即可
 *                              - 建议使用递增的正整数序列作为 "客户委托流水号" 的取值范围
 *                              - 客户委托流水号参见 @see OesOrdReqT.clSeqNo
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 *
 * @see         OesApi_InitAll
 * @see         OesApi_InitAllByCfgStruct
 */
BOOL    OesApi_InitAllByConvention(
                OesApiClientEnvT *pOutCliEnv,
                const char *pCfgFile,
                int64 lastRptSeqNum,
                int32 *pOutLastClSeqNo);

/**
 * 按照配置信息结构体, 初始化客户端环境
 *
 * @note        与 OesApi_InitAll 和 OesApi_InitAllByConvention 接口有一处不同,
 *              OesApi_InitAllByCfgStruct 接口不会自动初始化日志记录器, 需要在外面
 *              显式的调用 OesApi_InitLogger 来初始化API的日志记录器
 *
 * @param[out]  pOutCliEnv      输出客户端环境信息
 * @param       pClientCfg      配置信息结构体
 * @param       lastRptSeqNum   客户端最后接收到的回报数据的"回报编号(rptSeqNum)"
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *                              - 小于0, 从最新的数据开始推送回报数据
 *                              - 回报编号参见 @see OesRptMsgHeadT.rptSeqNum
 * @param[out]  pOutLastClSeqNo 返回服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 *                              - NULL表示忽略该参数
 *                              - "客户委托流水号" 是由客户端自行维护的委托流水, 用于标识
 *                                委托数据的唯一性, 并防止重复申报
 *                              - "客户委托流水号" 的取值范围没有限制, 只要维持在同一客户
 *                                端的同一个环境号(clEnvId)下的唯一即可
 *                              - 建议使用递增的正整数序列作为 "客户委托流水号" 的取值范围
 *                              - 客户委托流水号参见 @see OesOrdReqT.clSeqNo
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 *
 * @see         OesApi_InitAll
 * @see         OesApi_InitAllByConvention
 */
BOOL    OesApi_InitAllByCfgStruct(
                OesApiClientEnvT *pOutCliEnv,
                const OesApiClientCfgT *pClientCfg,
                int64 lastRptSeqNum,
                int32 *pOutLastClSeqNo);

/**
 * 注销并关闭所有的客户端会话
 *
 * @param[out]  pOutCliEnv      客户端环境信息
 * @param       isDestory       是否立即释放相关资源
 * @return      TRUE 成功; FALSE 失败
 */
void    OesApi_LogoutAll(
                OesApiClientEnvT *pOutCliEnv,
                BOOL isDestory);

/**
 * 直接断开与服务器的连接并释放会话数据
 *
 * @param[out]  pOutCliEnv      客户端环境信息
 */
void    OesApi_DestoryAll(
                OesApiClientEnvT *pOutCliEnv);
/* -------------------------           */


/* ===================================================================
 * 基于配置文件的辅助接口函数声明
 * =================================================================== */

/**
 * 初始化日志记录器
 *
 * @param   pCfgFile            配置文件路径
 * @param   pLoggerSection      日志记录器的配置区段名称(为空则使用默认值)
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_InitLogger(
                const char *pCfgFile,
                const char *pLoggerSection);

/**
 * 重置线程级别的日志记录器名称
 *
 * @param   pLogSystemName  线程级别的日志系统名称
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesApi_ResetThreadLoggerName(
                const char *pLogSystemName);

/**
 * 初始化委托申报通道 (包括完整的配置解析、连接建立和登录过程)
 *
 * @param[out]  pOutOrdChannel  委托申报通道的会话信息
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     客户端配置区段名称(为空则使用默认值)
 * @param       pAddrKey        地址列表的配置项关键字(为空则使用默认值)
 * @param[out]  pOutLastClSeqNo 返回服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 *                              - NULL表示忽略该参数
 *                              - "客户委托流水号" 是由客户端自行维护的委托流水, 用于标识
 *                                委托数据的唯一性, 并防止重复申报
 *                              - "客户委托流水号" 的取值范围没有限制, 只要维持在同一客户
 *                                端的同一个环境号(clEnvId)下的唯一即可
 *                              - 建议使用递增的正整数序列作为 "客户委托流水号" 的取值范围
 *                              - 客户委托流水号参见 @see OesOrdReqT.clSeqNo
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_InitOrdChannel(
                OesApiSessionInfoT *pOutOrdChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey,
                int32 *pOutLastClSeqNo);

/**
 * 初始化委托申报通道 (包括完整的连接建立和登录过程)
 *
 * @param[out]  pOutOrdChannel  委托申报通道的会话信息
 * @param       pRemoteCfg      远程主机配置信息
 * @param[out]  pOutLastClSeqNo 返回服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 *                              - NULL表示忽略该参数
 *                              - "客户委托流水号" 是由客户端自行维护的委托流水, 用于标识
 *                                委托数据的唯一性, 并防止重复申报
 *                              - "客户委托流水号" 的取值范围没有限制, 只要维持在同一客户
 *                                端的同一个环境号(clEnvId)下的唯一即可
 *                              - 建议使用递增的正整数序列作为 "客户委托流水号" 的取值范围
 *                              - 客户委托流水号参见 @see OesOrdReqT.clSeqNo
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_InitOrdChannel2(
                OesApiSessionInfoT *pOutOrdChannel,
                const OesApiRemoteCfgT *pRemoteCfg,
                int32 *pOutLastClSeqNo);

/**
 * 初始化回报通道 (包括完整的配置解析、连接建立和登录过程)
 *
 * @param[out]  pOutRptChannel  回报通道的会话信息
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     客户端配置区段名称(为空则使用默认值)
 * @param       pAddrKey        地址列表的配置项关键字(为空则使用默认值)
 * @param       lastRptSeqNum   客户端最后接收到的回报数据的"回报编号(rptSeqNum)"
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *                              - 小于0, 从最新的数据开始推送回报数据
 *                              - 回报编号参见 @see OesRptMsgHeadT.rptSeqNum
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_InitRptChannel(
                OesApiSessionInfoT *pOutRptChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey,
                int64 lastRptSeqNum);

/**
 * 初始化回报通道 (包括完整的连接建立和登录过程)
 *
 * @param[out]  pOutRptChannel  回报通道的会话信息
 * @param       pRemoteCfg      远程主机配置信息
 * @param       pSubscribeInfo  回报订阅配置信息,包括客户端环境号和订阅回报类型
 * @param       lastRptSeqNum   客户端最后接收到的回报数据的"回报编号(rptSeqNum)"
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *                              - 小于0, 从最新的数据开始推送回报数据
 *                              - 回报编号参见 @see OesRptMsgHeadT.rptSeqNum
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_InitRptChannel2(
                OesApiSessionInfoT *pOutRptChannel,
                const OesApiRemoteCfgT *pRemoteCfg,
                const OesApiSubscribeInfoT *pSubscribeInfo,
                int64 lastRptSeqNum);

/**
 * 初始化查询通道 (包括完整的配置解析、连接建立和登录过程)
 *
 * @param[out]  pOutQryChannel  查询通道的会话信息
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     客户端配置区段名称(为空则使用默认值)
 * @param       pAddrKey        地址列表的配置项关键字(为空则使用默认值)
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_InitQryChannel(
                OesApiSessionInfoT *pOutQryChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/**
 * 初始化查询通道 (包括完整的连接建立和登录过程)
 *
 * @param[out]  pOutQryChannel  查询通道的会话信息
 * @param       pRemoteCfg      远程主机配置信息
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   EACCES          用户名或密码错误
 * @exception   EMLINK          连接数量超过限制
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   ESRCH           登录节点非主节点
 * @exception   EFAULT          其他业务错误
 */
BOOL    OesApi_InitQryChannel2(
                OesApiSessionInfoT *pOutQryChannel,
                const OesApiRemoteCfgT *pRemoteCfg);

/**
 * 解析服务器地址列表字符串
 *
 * - 待解析的地址列表可是以空格、逗号或分号分割的地址列表字符串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同时也可以在每个地址之前, 为其指定对应的主机编号
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param       pUriList        主机地址列表 (以空格、逗号或分号分割的地址列表字符串)
 * @param[out]  pOutAddrList    用于输出解析后的地址信息的地址信息数组
 * @param       addrListLength  地址信息列表的数组长度
 * @return      大于等于0, 解析得到的地址数量; 小于0, 解析失败
 */
int32   OesApi_ParseAddrListString(
                const char *pUriList,
                OesApiAddrInfoT *pOutAddrList,
                int32 addrListLength);

/**
 * 从配置文件中解析远程主机配置
 *
 * @param       pCfgFile        配置文件路径
 * @param       pSection        配置区段名称
 * @param       pAddrKey        地址列表的配置项关键字
 * @param[out]  pOutRemoteCfg   输出远程主机配置信息
 * @param[out]  pOutSubscribeInfo
 *                              输出回报订阅信息
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesApi_ParseConfigFromFile(
                const char *pCfgFile,
                const char *pSection,
                const char *pAddrKey,
                OesApiRemoteCfgT *pOutRemoteCfg,
                OesApiSubscribeInfoT *pOutSubscribeInfo);

/**
 * 从配置文件中解析远程主机配置, 并可以指定是否允许配置项为空
 *
 * @param       pCfgFile        配置文件路径
 * @param       pSection        配置区段名称
 * @param       pAddrKey        地址列表的配置项关键字
 * @param[out]  pOutRemoteCfg   输出远程主机配置信息
 * @param[out]  pOutSubscribeInfo
 *                              输出回报订阅信息
 * @param       isRequiredCfg   是否必须配置 (是否允许配置项为空)
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesApi_ParseConfigFromFile2(
                const char *pCfgFile,
                const char *pSection,
                const char *pAddrKey,
                OesApiRemoteCfgT *pOutRemoteCfg,
                OesApiSubscribeInfoT *pOutSubscribeInfo,
                BOOL isRequiredCfg);

/**
 * 按照默认的配置名称, 从配置文件中解析所有配置信息
 *
 * @param       pCfgFile        配置文件路径
 * @param[out]  pOutApiCfg      输出远程主机配置信息
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesApi_ParseAllConfig(
                const char *pCfgFile,
                OesApiClientCfgT *pOutApiCfg);
/* -------------------------           */


/* ===================================================================
 * 用于同时接收多个连接通道数据的通道组接口函数
 * =================================================================== */

/**
 * 初始化(重置)通道组信息 (用于同时接收多个连接通道的数据)
 *
 * @param[in,out]   pChannelGroup
 *                              通道组信息
 * @return          TRUE, 成功; FALSE 失败
 */
BOOL    OesApi_InitChannelGroup(
                OesApiChannelGroupT *pChannelGroup);

/**
 * 销毁通道组信息 (同时关闭通道组下的所有连接)
 *
 * @param       pChannelGroup   通道组信息
 * @return      TRUE, 成功; FALSE 失败
 */
BOOL    OesApi_DestoryChannelGroup(
                OesApiChannelGroupT *pChannelGroup);

/**
 * 将连接信息添加到通道组
 *
 * @note        在检测通道组下各连接的I/O事件时, 是从后向前进行扫描的, 所以建议将更
 *              活跃的连接添加到其它连接的后面
 *
 * @param       pChannelGroup   通道组信息
 * @param       pChannel        连接信息
 * @return      TRUE, 成功; FALSE 失败
 */
BOOL    OesApi_AddToChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                OesApiSessionInfoT *pChannel);

/**
 * 从通道组中删除连接
 *
 * @param       pChannelGroup   通道组信息
 * @param       pTargetChannel  待删除连接的连接信息
 * @return      TRUE, 成功; FALSE 失败
 */
BOOL    OesApi_DeleteFromChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                OesApiSessionInfoT *pTargetChannel);

/**
 * 获取通道组中指定下标的连接信息
 *
 * @param       pChannelGroup   通道组信息
 * @param       index           下标位置 (如果小于0, 则表示按照先后顺序而非下标位置进行返回)
 *                              -  0, 返回 0 号下标位置所对应的会话信息
 *                              - -1, 返回通道组下第一个有效的会话信息
 *                              - -2, 返回通道组下第二个有效的会话信息
 *                              - INT_MIN, 如果超出了通道组的有效会话数量, 则返回最后一个有效的会话信息
 * @return      连接信息
 */
OesApiSessionInfoT *
        OesApi_GetFromChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                int32 index);

/**
 * 获取通道组中与指定Socket描述符相匹配的连接信息
 *
 * @param       pChannelGroup   通道组信息
 * @param       socketFd        Socket描述符
 * @return      连接信息
 */
OesApiSessionInfoT *
        OesApi_GetFromChannelGroupBySocket(
                OesApiChannelGroupT *pChannelGroup,
                SPK_SOCKET socketFd);

/**
 * 返回通道组最近接收消息时间
 *
 * @param   pChannelGroup       通道组信息
 * @return  通道组最近接收消息时间(单位: 秒)
 */
int64   OesApi_GetChannelGroupLastRecvTime(
                OesApiChannelGroupT *pChannelGroup);

/**
 * 返回通道组最近发送消息时间
 *
 * @param   pChannelGroup       通道组信息
 * @return  通道组最近发送消息时间(单位: 秒)
 */
int64   OesApi_GetChannelGroupLastSendTime(
                OesApiChannelGroupT *pChannelGroup);

/**
 * 遍历通道组下的所有通道信息并执行回调函数
 *
 * @param       pChannelGroup   通道组信息
 * @param       fnCallback      待执行的回调函数
 * @param       pParams         回调函数的参数
 * @return      0, 成功; 小于 0, errno 取负
 */
int32   OesApi_ForeachInChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                int32 (*fnCallback)(OesApiSessionInfoT *pChannel, void *pParams),
                void *pParams);

/**
 * 检测TCP通道组下各连接通道的读事件, 并调用回调函数进行消息处理
 *
 * @param       pChannelGroup   通道组信息
 * @param       timeoutMs       超时时间(毫秒)
 * @param       pOnMsgCallback  进行消息处理的回调函数
 * @param       pCallbackParams 回调函数的参数
 * @param[out]  ppOutFailed     返回处理失败时所对应的连接信息
 *                              - 允许为空, 为空则忽略该参数
 *                              - 当因为超时(一定时间内没有数据)而返回时, 该参数的值为空
 * @return      大于等于0, 成功 (返回回调函数的返回值);
 *              小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由select/read系统调用或回调函数返回的错误
 */
int32   OesApi_WaitOnChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_OESAPI_ON_RPT_MSG_T pOnMsgCallback,
                void *pCallbackParams,
                OesApiSessionInfoT **ppOutFailed);
/* -------------------------           */


/* ===================================================================
 * 错误处理等辅助函数
 * =================================================================== */

/**
 * 设置当前线程登录OES时使用的登录用户名
 * 不设置或者参数为空的话, 登录时会尝试使用配置文件中的配置
 *
 * @param   pUsername           登录用户名
 */
void    OesApi_SetThreadUsername(
                const char *pUsername);

/**
 * 返回当前线程登录OES时使用的登录用户名
 *
 * @return  登录用户名
 */
const char *
        OesApi_GetThreadUsername();

/**
 * 设置当前线程登录OES时使用的登录密码
 * 不设置或者参数为空的话, 登录时会尝试使用配置文件中的配置
 *
 * @param   pPassword           登录密码
 *                              - 支持通过密码前缀指定密码类型, 如 md5:PASSWORD, txt:PASSWORD
 */
void    OesApi_SetThreadPassword(
                const char *pPassword);

/**
 * 设置当前线程登录OES时使用的客户端环境号
 * 不设置或者参数为空的话, 登录时会尝试使用配置文件中的配置
 *
 * @param   clEnvId             客户端环境号
 */
void    OesApi_SetThreadEnvId(
                int8 clEnvId);

/**
 * 返回当前线程登录OES时使用的客户端环境号
 *
 * @return  客户端环境号
 */
int8    OesApi_GetThreadEnvId();

/**
 * 设置当前线程订阅回报使用的客户端环境号
 * 不设置或者参数为空的话, 会尝试使用配置文件中的配置
 *
 * @param   subscribeEnvId      待订阅的客户端环境号
 */
void    OesApi_SetThreadSubscribeEnvId(
                int8 subscribeEnvId);

/**
 * 返回当前线程订阅回报使用的客户端环境号
 *
 * @return  客户端环境号
 */
int8    OesApi_GetThreadSubscribeEnvId();

/**
 * 设置客户端自定义的本地IP和MAC
 *
 * @param   pIpStr              点分十进制的IP地址字符串
 * @param   pMacStr             MAC地址字符串 (MAC地址格式 45:38:56:89:78:5A)
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    OesApi_SetCustomizedIpAndMac(
                const char *pIpStr,
                const char *pMacStr);

/**
 * 设置客户端自定义的本地IP地址
 *
 * @param   pIpStr              点分十进制的IP地址字符串
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    OesApi_SetCustomizedIp(
                const char *pIpStr);

/**
 * 设置客户端自定义的本地MAC地址
 *
 * @param   pMacStr             MAC地址字符串 (MAC地址格式 45:38:56:89:78:5A)
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    OesApi_SetCustomizedMac(
                const char *pMacStr);

/**
 * 获取客户端自定义的本地IP
 *
 * @return  客户端自定义的本地IP
 */
const char *
        OesApi_GetCustomizedIp();

/**
 * 获取客户端自定义的本地MAC
 *
 * @return  客户端自定义的本地MAC
 */
const char *
        OesApi_GetCustomizedMac();

/**
 * 设置客户端自定义的本地设备序列号
 *
 * @param   pDriverId           设备序列号字符串
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    OesApi_SetCustomizedDriverId(
                const char *pDriverId);

/**
 * 获取客户端自定义的本地设备序列号
 *
 * @return  客户端自定义的本地设备序列号
 */
const char *
        OesApi_GetCustomizedDriverId();

/**
 * 返回通道对应的客户端环境号 (clEnvId)
 *
 * @param   pSessionInfo        会话信息
 * @return  通道对应的客户端环境号
 */
int8    OesApi_GetClEnvId(
                const OesApiSessionInfoT *pSessionInfo);

/**
 * 返回系统是否支持指定的业务类别 (businessScope)
 *
 * @param   pSessionInfo        会话信息
 * @param   businessScope       业务类别 @see eOesBusinessScopeT
 * @return  TRUE 支持; FALSE 不支持
 */
BOOL    OesApi_IsBusinessSupported(
                const OesApiSessionInfoT *pSessionInfo,
                eOesBusinessScopeT businessScope);

/**
 * 获取通道最近接收消息时间
 *
 * @param   pSessionInfo        会话信息
 * @return  通道最近接收消息时间(单位: 秒)
 */
int64   OesApi_GetLastRecvTime(
                const OesApiSessionInfoT *pSessionInfo);

/**
 * 获取通道最近发送消息时间
 *
 * @param   pSessionInfo        会话信息
 * @return  通道最近发送消息时间(单位: 秒)
 */
int64   OesApi_GetLastSendTime(
                const OesApiSessionInfoT *pSessionInfo);

/**
 * 返回回报通道是否还有更多已接收但尚未回调处理完成的数据
 *
 * @param   pRptChannel         会话信息
 * @return  已接收到但尚未处理完成的数据长度
 * @note    当在回调函数里面调用时, 该接口返回的数据长度是包含本次回调数据的
 */
int32   OesApi_HasMoreCachedData(
                const OesApiSessionInfoT *pRptChannel);

/**
 * 返回委托申报通道是否已经连接且有效
 *
 * @param   pOrdChannel         会话信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    OesApi_IsValidOrdChannel(
                const OesApiSessionInfoT *pOrdChannel);

/**
 * 返回回报通道是否已经连接且有效
 *
 * @param   pRptChannel         会话信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    OesApi_IsValidRptChannel(
                const OesApiSessionInfoT *pRptChannel);

/**
 * 返回查询通道是否已经连接且有效
 *
 * @param   pQryChannel         会话信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    OesApi_IsValidQryChannel(
                const OesApiSessionInfoT *pQryChannel);

/**
 * 返回通道组是否已经连接
 *
 * @param   pChannelGroup       通道组信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    OesApi_IsValidChannelGroup(
                const OesApiChannelGroupT *pChannelGroup);

/**
 * 返回当前线程最近一次API调用失败的错误号
 *
 * @return  错误号
 */
int32   OesApi_GetLastError();

/**
 * 设置当前线程的API错误号
 *
 * @param   errCode             错误号
 */
void    OesApi_SetLastError(
                int32 errCode);

/**
 * 返回错误号对应的错误信息
 *
 * @param   errCode             错误号
 * @return  错误号对应的错误信息
 */
const char *
        OesApi_GetErrorMsg(
                int32 errCode);

/**
 * 返回消息头中的状态码所对应的错误信息
 *
 * @param   status              状态码
 * @param   detailStatus        明细状态码
 * @return  状态码所对应的错误信息
 */
const char *
        OesApi_GetErrorMsg2(
                uint8 status,
                uint8 detailStatus);

/**
 * 返回指定错误码是否属于指定错误信息条目
 *
 * @param   errCode             错误编码
 * @param   pErr                错误信息条目
 * @return  TRUE 属于; FALSE 不属于
 */
BOOL    OesApi_IsErrorOf(
                int32 errCode,
                const SErrMsgT *pErrMsg);

/**
 * 返回消息头中的状态码是否属于指定错误信息条目
 *
 * @param   status              状态码
 * @param   detailStatus        明细状态码
 * @param   pErr                错误信息条目
 * @return  TRUE 属于; FALSE 不属于
 */
BOOL    OesApi_IsErrorOf2(
                uint8 status,
                uint8 detailStatus,
                const SErrMsgT *pErrMsg);

/**
 * 返回现货产品是否具有指定状态
 * 根据证券状态'securityStatus'字段判断 @see OesStockItemT
 *
 * @param   pStockItem          现货产品信息
 * @param   status              指定的状态 @see eOesSecurityStatusT
 * @return  TRUE 具有指定的状态; FALSE 没有指定的状态
 */
BOOL    OesApi_HasStockStatus(
                const OesStockItemT *pStockItem,
                eOesSecurityStatusT status);
/* -------------------------           */


/* ===================================================================
 * 其它辅助函数
 * =================================================================== */

/**
 * 从成交回报中提取和生成委托回报信息
 *
 * @note        与原生委托回报相比, 缺少如下字段:
 *              - 缺少 exchOrdId, 将置为空
 *              - 缺少 frzAmt, 将置为0
 *              - 缺少 frzInterest, 将置为0
 *              - 缺少 frzFee, 将置为0
 *              - 另外, 还缺少原始的委托时间(ordTime)和委托确认时间(ordCnfmTime), 将使
 *                用成交时间(trdTime)替代
 *
 * @param[in]   pTrdReport      成交回报信息
 * @param[out]  pOutOrdReport   用于输出委托回报信息的缓存区
 * @return      提取到的委托回报信息
 */
OesOrdCnfmT *
        OesHelper_ExtractOrdReportFromTrd(
                const OesTrdCnfmT *pTrdReport,
                OesOrdCnfmT *pOutOrdReport);
/* -------------------------           */


/* ===================================================================
 * 用于校验API版本号是否匹配的标识函数定义
 * =================================================================== */

#define __OESAPI_METHOD_IsApiVersionMatched_NAME2(VER)          \
        __OesApi_IsApiVersionMatched__##VER

#define __OESAPI_METHOD_IsApiVersionMatched_NAME(VER)           \
        __OESAPI_METHOD_IsApiVersionMatched_NAME2(VER)

#define __OESAPI_METHOD_IsApiVersionMatched                     \
        __OESAPI_METHOD_IsApiVersionMatched_NAME(OES_APPL_VER_VALUE)


/* 用于校验API版本号是否匹配的标识函数 (如果链接时报函数不存在错误, 请检查API的头文件与库文件是否一致) */
BOOL    __OESAPI_METHOD_IsApiVersionMatched();
/* -------------------------           */


/* ===================================================================
 * 辅助的内联函数定义
 * =================================================================== */

/**
 * 检查API版本是否匹配 (检查API头文件和库文件的版本是否匹配)
 *
 * @return  TRUE 匹配; FALSE 不匹配
 */
static __inline BOOL
__OesApi_CheckApiVersion() {

    /* 如果编译时报 IsApiVersionMatched 函数不存在错误, 请检查API的头文件与库文件是否一致 */
    if (__OESAPI_METHOD_IsApiVersionMatched()
            && strcmp(OesApi_GetApiVersion(), OES_APPL_VER_ID) == 0) {
        return TRUE;
    }
    return FALSE;
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_API_H */
