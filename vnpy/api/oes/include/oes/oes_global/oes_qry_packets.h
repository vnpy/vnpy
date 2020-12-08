/*
 * Copyright 2009-2015 the original author or authors.
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
 * @file    oes_qry_packets.h
 *
 * 查询消息的报文定义
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 增加客户信息查询功能
 *          - ETF成份股查询应答中增加成份股所属ETF申赎代码
 *          - 佣金查询应答中增加客户代码
 *          - 在登录报文中增加协议版本号信息, 并在登录时校验协议版本号的兼容性
 * @version 0.12.1      2016/12/19
 *          - 整合查询消息中的qryCnt、position等字段, 成为一个新的结构体 OesQryHeadT
 * @version 0.12.3      2017/01/10
 *          - OesHoldItemT 结构体拆分成 OesStkHoldingItemT、OesOptHoldingItemT两个结构体
 *          - 持仓查询相关结构体拆分成股票持仓查询、期权持仓查询专用的结构体
 * @version 0.12.3.5    2017/02/20
 *          - 佣金查询过滤条件中新增一条“证券子类型”的过滤条件
 * @version 0.12.6.2    2017/03/16
 *          - '查询出入金流水信息过滤条件' 中重命名 cashSeqNo => clSeqNo
 *          - 调整查询到的 '出入金流水信息' 结构 (与出入金委托执行回报结构一致)
 *          - 调整佣金查询结果中feeRate字段的精度, 当佣金计算模式为 '按金额' 时,
 *            feeRate 字段所代表的比率单位由 '十万分之一' => '百万分之一'
 * @version 0.12.8.2    2017/05/09
 *          - 客户资金信息(OesCashAssetItemT)中添加字段 '当前冲正金额(红冲蓝补的资金净额, reversalAmt)'
 * @version 0.12.8.2    2017/05/16
 *          - 新增 '证券发行信息查询' 相关报文定义
 *              - 新增结构体 查询证券发行信息过滤条件(OesQryIssueFilterT)
 *              - 新增结构体 证券发行信息内容(OesIssueItemT)
 *              - 新增结构体 查询证券发行信息请求(OesQryIssueReqT)
 *              - 新增结构体 查询证券发行信息应答(OesQryIssueRspT)
 * @version 0.12.9_RC1  2017/06/05
 *          - 调整佣金查询结果中feeRate字段的精度, 当佣金计算模式为 '按份数' 时,
 *              feeRate 字段所代表的比率单位由 '万分之一' => '百万分之一'
 * @version 0.15.1      2017/06/26
 *          - '委托查询的过滤条件(OesQryOrdFilterT)' 中
 *              - 新增字段 委托的起始时间(startTime) 和 委托的结束时间(endTime)
 *          - '成交查询的过滤条件(OesQryTrdFilterT)' 中
 *              - 新增字段 成交的起始时间(startTime) 和 成交的结束时间(endTime)
 *          - '持仓查询的返回信息(OesStkHoldingItemT)' 中新增字段 总持仓(sumHld)
 *          - '资金查询的返回信息(OesCashAssetItemT)' 中
 *              - 新增字段 当前余额(currentBal)
 *              - 字段重命名 当前可用余额(tradeAvlAmt => currentAvailableBal)
 *              - 字段重命名 当前可取余额(withdrawAvlAmt => currentDrawableBal)
 * @version 0.15.2      2017/07/18
 *          - 新增 '新股认购、中签信息查询' 相关报文定义
 *              - 新增结构体 查询新股认购、中签信息过滤条件(OesQryLotWinningFilterT)
 *              - 新增结构体 新股认购、中签信息内容(OesLotWinningItemT)
 *              - 新增结构体 查询新股认购、中签信息请求(OesQryLotWinningReqT)
 *              - 新增结构体 查询新股认购、中签信息应答(OesQryLotWinningRspT)
 * @version 0.15.4      2017/09/04
 *          - 查询请求中消息头的类型由 'OesQryHeadT' 改为 'OesQryReqHeadT'
 *          - 查询应答中消息头的类型由 'OesQryHeadT' 改为 'OesQryRspHeadT'
 *          - 删除 'OesQryHeadT' 类型定义
 *          - '委托信息查询结果 (OesOrdItemT)' 中增加字段:
 *              - 客户端编号 (clientId)
 *              - 客户端环境号 (clEnvId)
 *              - 原始订单的客户委托流水号 (origClSeqNo)
 *              - 原始订单的客户端环境号 (origClEnvId)
 *              - 交易所订单编号 (exchOrdId)
 *          - '成交信息查询结果 (OesTrdItemT)' 中增加字段:
 *              - 客户端编号 (clientId)
 *              - 客户端环境号 (clEnvId)
 *          - '股票持仓信息 (OesStkHoldingItemT)' 中增加字段:
 *              - 持仓成本 (costAmount)
 *              - 持仓成本价 (costPrice)
 *          - 整理以下结构体定义, 调整了字段顺序, 并删除了个别字段
 *              - 现货产品信息查询结果 (OesStockItemT)
 *              - 期权产品信息查询结果 (OesOptionItemT)
 *              - 证券账户信息查询结果 (OesInvAcctItemT)
 *          - 所有的查询过滤条件(OesQryXXXFilterT) 中增加 userInfo字段,
 *              此字段会在对应的查询应答消息(OesQryXXXRspT) 的应答头中原样带回
 * @version 0.15.5      2017/11/03
 *          - 调整查询应答报文中携带查询数据的最大条目数量
 *          - 调整 '查询请求消息头(OesQryReqHeadT)' 中部分字段：
 *              - '查询窗口大小'字段重命名 pageSize => maxPageSize
 *              - '查询起始位置'字段重命名 position => lastPosition
 *          - 调整 '查询应答消息头(OesQryRspHeadT)' 中部分字段：
 *              - '查询到的信息条目数'字段重命名 itemCnt => itemCount
 *              - '查询到的最后一条信息的位置'字段重命名 position => lastPosition
 *          - 调整 '查询应答消息头(OesQryRspHeadT)' 中部分字段：
 *              - '查询到的信息条目数'字段重命名 itemCnt => itemCount
 *              - '查询到的最后一条信息的位置'字段重命名 position => lastPosition
 *          - '股票持仓信息 (OesStkHoldingItemT)' 结构体中增加字段:
 *              - 证券类型 (securityType)
 *              - 证券子类型 (subSecurityType)
 *          - 调整 '资金信息(OesCashAssetItemT)' 中部分字段:
 *              - '当前余额'字段重命名 currentBal => currentTotalBal
 * @version 0.15.5.2    2018/01/29
 *          - 修正 '佣金查询结果 (OesCommissionRateItemT)' 中 feeRate 字段精度描述不正确的问题
 * @version 0.15.5.6    2018/04/01
 *          - 新增 '市场状态信息查询' 相关报文定义
 *              - 新增结构体 查询市场状态信息过滤条件(OesQryMarketStateFilterT)
 *              - 新增结构体 市场状态信息内容(OesMarketStateItemT)
 *              - 新增结构体 查询市场状态信息请求(OesQryMarketStateReqT)
 *              - 新增结构体 查询市场状态信息应答(OesQryMarketStateRspT)
 * @version 0.15.5.14   2018/08/01
 *          - '现货产品信息查询过滤条件(OesQryStockFilterT)' 中新增字段:
 *              - 证券类别(securityType)
 *              - 证券子类别(subSecurityType)
 * @version 0.15.5.16   2018/08/31
 *          - 新增 '查询客户端总览信息' 相关报文定义
 *              - 新增结构体 股东账户总览信息(OesInvAcctOverviewT)
 *              - 新增结构体 资金账户总览信息(OesCashAcctOverviewT)
 *              - 新增结构体 客户总览信息(OesCustOverviewT)
 *              - 新增结构体 客户端总览信息(OesClientOverviewT)
 *              - 新增结构体 主柜资金信息(OesCounterCashItemT)
 *          - 新增 '查询主柜资金信息' 相关报文定义
 *              - 新增结构体 查询主柜资金信息请求(OesQryCounterCashReqT)
 *              - 新增结构体 查询主柜资金信息应答(OesQryCounterCashRspT)
 *              - 新增结构体 主柜资金信息内容(OesCounterCashItemT)
 *          - '客户资金信息内容(OesCashAssetItemT)' 中新增 是否禁止出入金(isFundTrsfDisabled) 字段
 *          - '证券账户信息内容(OesInvAcctItemT)' 中新增 是否禁止交易(isTradeDisabled) 字段
 * @version 0.15.5.16_u3 2018/09/28
 *          - 调整成交信息(OesTrdItemT)的结构体字段
 *              - 调整 v0.15.5.16 版本新增的 '证券子类别(subSecurityType)' 字段的位置
 *              - 增加 '原始委托数量(origOrdQty)' 和 '原始委托价格(origOrdPrice)' 字段
 * @version 0.15.6.14   2018/08/01
 *          - '委托查询的过滤条件(OesQryOrdFilterT)' 中
 *              - 新增字段 证券类别(securityType) 和 买卖类型(bsType)
 *          - '成交查询的过滤条件(OesQryTrdFilterT)' 中
 *              - 新增字段 证券类别(securityType) 和 买卖类型(bsType)
 *          - '股票持仓查询的过滤条件(OesQryStkHoldingFilterT)' 中
 *              - 新增字段 证券类别(securityType)
 * @version 0.15.7.6   2018/11/03
 *          - '证券发行信息查询的过滤条件(OesQryIssueFilterT)' 中
 *              - 新增字段 '产品类型 (productType)'
 *          - '查询股票持仓信息过滤条件(OesQryStkHoldingFilterT)' 中
 *              - 新增字段 '产品类型 (productType)'
 * @version 0.15.9      2019/03/12
 *          - 为了支持科创板, 扩展以下查询结果 (兼容之前版本的API)
 *              - 证券账户信息 (OesInvAcctItemT) 中增加如下字段:
 *                  - 科创板权益 (kcSubscriptionQuota)
 *              - 现货产品信息 (OesStockItemT) 中增加如下字段:
 *                  - 限价买数量上限 (lmtBuyMaxQty)
 *                  - 限价买数量下限 (lmtBuyMinQty)
 *                  - 限价卖数量上限 (lmtSellMaxQty)
 *                  - 限价卖数量下限 (lmtSellMinQty)
 *                  - 市价买数量上限 (mktBuyMaxQty)
 *                  - 市价买数量下限 (mktBuyMinQty)
 *                  - 市价卖数量上限 (mktSellMaxQty)
 *                  - 市价卖数量下限 (mktSellMinQty)
 *              - 客户端总览信息中的股东账户总览 (OesInvAcctOverviewT) 中增加如下字段:
 *                  - 科创板权益 (kcSubscriptionQuota)
 * @version 0.15.9_u4   2019/12/03
 *          - '证券发行信息 (OesIssueItemT)' 结构中增加字段:
 *                  - 停牌标识 (suspFlag)
 *                  - 发行方式 (issueType)
 * @version 0.15.9.1    2019/08/02
 *          - 新增 '券商参数信息查询' 相关报文定义
 *              - 新增 券商参数信息内容(OesBrokerParamsInfoT)
 * @version 0.15.9.4    2019/12/24
 *          - '现货产品基础信息 (OesStockBaseInfoT)' 结构中增加字段:
 *              - 总股本 (outstandingShare)
 *              - 流通股数量 (publicFloatShare)
 *          - '证券账户基础信息 (OesInvAcctBaseInfoT)' 结构中增加字段:
 *              - 个股持仓比例阀值(stkPositionLimitRatio)
 * @version 0.15.10.1   2020/01/17
 *          - '股票持仓信息 (OesStkHoldingItemT)' 中
 *              - 删除 当前已锁定持仓 (lockHld) 字段
 *              - 删除 当前锁定冻结持仓 (lockFrzHld) 字段
 *              - 删除 当前解锁定冻结持仓数量 (unlockFrzHld) 字段
 *              - 删除 当前备兑冻结的现货持仓数量 (coveredFrzHld) 字段
 *              - 删除 当前已备兑使用的现货持仓数量 (coveredHld) 字段
 *              - 删除 当前可用于备兑的现货持仓 (coveredAvlHld) 字段
 *              - 新增 日初可用持仓 (originalAvlHld) 字段
 *              - 新增 日初锁定持仓 (originalLockHld) 字段
 *              - 新增 日中累计锁定持仓 (totalLockHld) 字段
 *              - 新增 日中累计解锁持仓 (totalUnlockHld) 字段
 *              - 新增 当日最大可减持额度 (maxReduceQuota) 字段
 *          - '客户端总览信息内容 (OesClientOverviewT)' 中
 *              - 新增 客户端适用的业务范围 (businessScope) 字段
 * @version 0.15.11     2020/05/29
 *          - 为了支持创业版, 扩展以下查询结果
 *              - 现货产品信息 (OesStockItemT) 中:
 *                  - 新增 证券状态 (securityStatus) 字段
 *                  - 新增 证券属性 (securityAttribute) 保留字段
 *                  - 新增 是否注册制 (isRegistration) 字段
 *                  - 新增 是否为融资标的 (isCrdMarginTradeUnderlying) 字段
 *                  - 新增 是否为融券标的 (isCrdShortSellUnderlying) 字段
 *                  - 新增 是否为融资融券担保品 (isCrdCollateral) 字段
 *                  - 新增 是否尚未盈利 (isNoProfit) 字段
 *                  - 新增 是否存在投票权差异 (isWeightedVotingRights) 字段
 *                  - 新增 是否具有协议控制框架 (isVie) 字段
 *                  - 重构 限价买入单位 (lmtBuyQtyUnit) 字段, 增加新的别名
 *                      - buyQtyUnit => lmtBuyQtyUnit
 *                  - 重构 限价卖出单位 (lmtSellQtyUnit) 字段, 增加新的别名
 *                      - sellQtyUnit => lmtSellQtyUnit
 *                  - 新增 市价买入单位 (mktBuyQtyUnit) 字段
 *                  - 新增 市价卖出单位 (mktSellQtyUnit) 字段
 *                  - 重构 面值 (parPrice) 字段, 增加新的别名  (兼容之前版本的API)
 *                      - parPrice => parValue
 *                  - 新增 连续竞价范围限制类型 (auctionLimitType) 字段
 *                  - 新增 连续竞价范围基准价类型 (auctionReferPriceType) 字段
 *                  - 新增 连续竞价范围涨跌幅度 (auctionUpDownRange) 字段
 *                  - 新增 上市日期 (listDate) 字段
 *                  - 新增 到期日期 (maturityDate) 字段
 *                  - 新增 基础证券代码 (underlyingSecurityId) 字段
 *              - 证券发行信息 (OesIssueItemT) 中:
 *                  - 新增 是否注册制 (isRegistration) 字段
 *                  - 新增 证券属性 (securityAttribute) 保留字段
 *                  - 新增 是否尚未盈利 (isNoProfit) 字段
 *                  - 新增 是否存在投票权差异 (isWeightedVotingRights) 字段
 *                  - 新增 是否具有协议控制框架 (isVie) 字段
 *                  - 新增 配股股权登记日 (alotRecordDay) 字段
 *                  - 新增 配股股权除权日 (alotExRightsDay) 字段
 *          - 调整查询ETF成份证券信息接口
 *              - 查询ETF成份证券信息过滤条件 (OesQryEtfComponentFilterT) 中:
 *                  - 查询条件 ETF基金申赎代码 (fundId) 不再是必填项
 *                  - 新增查询条件 ETF基金市场代码 (fundMktId)
 *              - 'ETF基金成份证券信息 (OesEtfComponentItemT)' 中:
 *                  - 新增 ETF基金市场代码 (fundMktId) 字段
 *                  - 新增 是否是作为申赎对价的成份证券 (isTrdComponent) 字段
 *                  - 新增 赎回折价比例 (discountRatio) 字段
 *                  - 新增 成份证券名称 (securityName) 字段
 *                  - 重构 申购溢价比例、赎回替代金额 字段命名, 为这些字段增加新的别名 (兼容之前版本的API)
 *                      - premiumRate => premiumRatio
 *                      - redemptionCashSub => redemptionSubCash
 * @version 0.16        2019/01/18
 *          - '股票持仓信息 (OesStkHoldingItemT)'中
 *              - 删除 当前已锁定持仓 (lockHld) 字段
 *              - 删除 当前锁定冻结持仓 (lockFrzHld) 字段
 *              - 删除 当前解锁定冻结持仓数量 (unlockFrzHld) 字段
 *              - 删除 当前备兑冻结的现货持仓数量 (coveredFrzHld) 字段
 *              - 删除 当前已备兑使用的现货持仓数量 (coveredHld) 字段
 *              - 删除 当前可用于备兑的现货持仓 (coveredAvlHld) 字段
 *              - 新增 日初可用持仓 (originalAvlHld) 字段
 *              - 新增 日初锁定持仓 (originalLockHld) 字段
 *              - 新增 日中累计锁定持仓 (totalLockHld) 字段
 *              - 新增 日中累计解锁持仓 (totalUnlockHld) 字段
 *          - '客户资金信息 (OesCashAssetItemT)' 中
 *              - 新增 日初持仓占用保证金 (initialMargin) 字段
 *              - 新增 行权待交收冻结资金 (totalExerciseFrzAmt) 字段
 *              - 新增 待追加保证金 (pendingSupplMargin) 字段
 *              - 新增 上海市场可用限购额度 (sseAvailablePurchaseLimit) 字段
 *              - 新增 深圳市场可用限购额度 (szseAvailablePurchaseLimit) 字段
 *          - 新增 '通知消息查询' 相关报文定义
 *              - 新增结构体 查询通知消息过滤条件(OesQryNotifyInfoFilterT)
 *              - 新增结构体 通知消息内容(OesNotifyInfoItemT)
 *              - 新增结构体 查询通知消息请求(OesQryNotifyInfoReqT)
 *              - 新增结构体 查询通知消息应答(OesQryNotifyInfoRspT)
 *          - 新增 '期权限仓额度查询' 相关报文定义
 *              - 新增结构体 查询期权限仓额度消息过滤条件(OesQryOptPositionLimitFilterT)
 *              - 新增结构体 期权限仓额度信息内容(OesOptPositionLimitItemT)
 *              - 新增结构体 查询期权限仓额度消息请求(OesQryOptPositionLimitReqT)
 *              - 新增结构体 查询期权限仓额度消息应答(OesQryOptPositionLimitRspT)
 *          - 新增 '期权限购额度信息查询' 相关报文定义
 *              - 新增结构体 查询期权限购额度信息过滤条件(OesQryOptPurchaseLimitFilterT)
 *              - 新增结构体 期权限购额度信息内容(OesOptPurchaseLimitItemT)
 *              - 新增结构体 查询期权限购额度信息请求(OesQryOptPurchaseLimitReqT)
 *              - 新增结构体 查询期权限购额度信息应答(OesQryOptPurchaseLimitRspT)
 *          - 新增 '期权行权指派查询' 相关报文定义
 *              - 新增结构体 查询期权行权指派消息过滤条件(OesQryOptExerciseAssignFilterT)
 *              - 新增结构体 期权行权指派信息内容(OesOptxerciseAssignItemT)
 *              - 新增结构体 查询期权行权指派消息请求(OesQryOptExerciseAssignReqT)
 *              - 新增结构体 查询期权行权指派消息应答(OesQryOptExerciseAssignRspT)
 * @version 0.16.0.2    2020/01/03
 *          - '券商参数信息 (OesBrokerParamsInfoT)' 中
 *              - 新增 服务端业务范围 (businessScope) 字段
 *              - 新增 期权扩展参数 (optionExt) 结构, 其中新增 投资人出金提取线 (withdrawLineRatio) 字段
 *          - '期权行权指派信息 (OesOptExerciseAssignItemT)'中
 *              - 新增 期权合约名称 (securityName) 字段
 * @version 0.16.0.4    2020/02/28
 *          - '期权标的持仓信息 (OesOptUnderlyingHoldingItemT)'中
 *              - 新增 当日最大可减持额度 (maxReduceQuota) 字段
 *          - '客户资金信息 (OesCashAssetItemT)' 中
 *              - 新增 未对冲实时价格保证金 (totalMarketMargin) 字段
 *              - 新增 已对冲实时价格保证金 (totalNetMargin) 字段
 *
 * @since   2015/07/30
 */


#ifndef _OES_QRY_PACKETS_H
#define _OES_QRY_PACKETS_H


#include    <oes_global/oes_base_model.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 每条查询应答报文中委托信息的最大数量 */
#define OES_MAX_ORD_ITEM_CNT_PER_PACK               (30)

/** 每条查询应答报文中成交信息的最大数量 */
#define OES_MAX_TRD_ITEM_CNT_PER_PACK               (30)

/** 每条查询应答报文中客户资金信息的最大数量 */
#define OES_MAX_CASH_ASSET_ITEM_CNT_PER_PACK        (30)

/** 每条查询应答报文中持仓信息的最大数量 */
#define OES_MAX_HOLDING_ITEM_CNT_PER_PACK           (30)

/** 每条查询应答报文中客户信息的最大数量 */
#define OES_MAX_CUST_ITEM_CNT_PER_PACK              (30)

/** 每条查询应答报文中证券账户信息的最大数量 */
#define OES_MAX_INV_ACCT_ITEM_CNT_PER_PACK          (30)

/** 每条查询应答报文中客户佣金信息的最大数量 */
#define OES_MAX_COMMS_RATE_ITEM_CNT_PER_PACK        (50)

/** 每条查询应答报文中出入金流水记录的最大数量 */
#define OES_MAX_FUND_TRSF_ITEM_CNT_PER_PACK         (30)

/** 每条查询应答报文中新股认购、中签信息的最大数量 */
#define OES_MAX_LOG_WINNING_ITEM_CNT_PER_PACK       (30)

/** 每条查询应答报文中证券发行信息的最大数量 */
#define OES_MAX_ISSUE_ITEM_CNT_PER_PACK             (30)

/** 每条查询应答报文中现货产品信息的最大数量 */
#define OES_MAX_STOCK_ITEM_CNT_PER_PACK             (30)

/** 每条查询应答报文中ETF申赎产品信息的最大数量 */
#define OES_MAX_ETF_ITEM_CNT_PER_PACK               (30)

/** 每条查询应答报文中ETF成份证券的最大数量 */
#define OES_MAX_ETF_COMPONENT_ITEM_CNT_PER_PACK     (30)

/** 每条查询应答报文中期权产品的最大数量 */
#define OES_MAX_OPTION_ITEM_CNT_PER_PACK            (30)

/** 每条查询应答报文中市场状态的最大数量 */
#define OES_MAX_MKT_STATE_ITEM_CNT_PER_PACK         (30)

/** 每条查询应答报文中通知消息的最大数量 */
#define OES_MAX_NOTIFY_INFO_ITEM_CNT_PER_PACK       (30)

/** 每条查询应答报文中期权标的信息的最大数量 */
#define OES_MAX_OPT_UNDERLYING_ITEM_CNT_PER_PACK    (30)

/** 每条查询应答报文中期权限购额度信息的最大数量 */
#define OES_MAX_OPT_PURCHASE_LIMIT_ITEM_CNT_PER_PACK    \
                                                    (30)
/** 每条查询应答报文中期权行权指派信息的最大数量 */
#define OES_MAX_EXERCISE_ASSIGN_ITEM_CNT_PER_PACK   (30)

/** 客户端对应的最大客户数量 */
#define OES_MAX_CUST_PER_CLIENT                     (1)
/* -------------------------           */


/* ===================================================================
 * 查询消息头相关结构体定义
 * =================================================================== */

/**
 * 查询定位的游标结构
 */
typedef struct _OesQryCursor {
    /** 查询位置 */
    int32               seqNo;

    /** 是否是当前最后一个包 */
    int8                isEnd;
    /** 按64位对齐填充域 */
    int8                __filler[3];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCursorT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CURSOR                          \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询请求的消息头定义
 */
typedef struct _OesQryReqHead {
    /** 查询窗口大小 */
    int32               maxPageSize;
    /** 查询起始位置 */
    int32               lastPosition;
} OesQryReqHeadT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_REQ_HEAD                        \
        0, 0
/* -------------------------           */


/**
 * 查询应答的消息头定义
 */
typedef struct _OesQryRspHead {
    /** 查询到的信息条目数 */
    int32               itemCount;
    /** 查询到的最后一条信息的位置 */
    int32               lastPosition;

    /** 是否是当前查询最后一个包 */
    int8                isEnd;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryRspHeadT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_RSP_HEAD                        \
        0, 0, 0, {0}, 0
/* -------------------------           */


/* ===================================================================
 * 查询委托信息相关结构体定义
 * =================================================================== */

/**
 * 查询委托信息过滤条件
 */
typedef struct _OesQryOrdFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 是否仅查询未关闭委托 (包括未全部成交或撤销的委托) */
    uint8               isUnclosedOnly;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 买卖类型  @see eOesBuySellTypeT */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint8               __filler[3];

    /** 客户委托编号, 可选项 */
    int64               clOrdId;
    /** 客户委托流水号, 可选项 */
    int64               clSeqNo;

    /** 查询委托的起始时间 (格式为 HHMMSSsss, 比如 141205000 表示 14:12:05.000) */
    int32               startTime;
    /** 查询委托的结束时间 (格式为 HHMMSSsss, 比如 141205000 表示 14:12:05.000) */
    int32               endTime;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOrdFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ORD_FILTER                      \
        {0}, {0}, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询到的委托信息内容
 */
typedef OesOrdCnfmT     OesOrdItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ORD_ITEM                            \
        NULLOBJ_OES_ORD_CNFM
/* -------------------------           */


/**
 * 查询委托信息请求
 */
typedef struct _OesQryOrdReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryOrdFilterT    qryFilter;
} OesQryOrdReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ORD_REQ                         \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ORD_FILTER}
/* -------------------------           */


/**
 * 查询委托信息应答
 */
typedef struct _OesQryOrdRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 委托信息数组 */
    OesOrdItemT         qryItems[OES_MAX_ORD_ITEM_CNT_PER_PACK];
} OesQryOrdRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ORD_RSP                         \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ORD_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询成交信息相关结构体定义
 * =================================================================== */

/**
 * 查询成交信息过滤条件
 */
typedef struct _OesQryTrdFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 买卖类型  @see eOesBuySellTypeT */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint32              __filler;

    /** 内部委托编号, 可选项 */
    int64               clOrdId;
    /** 客户委托流水号, 可选项 */
    int64               clSeqNo;

    /** 成交开始时间 (格式为 HHMMSSsss, 形如 141205000) */
    int32               startTime;
    /** 成交结束时间 */
    int32               endTime;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryTrdFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRD_FILTER                      \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询到的成交信息内容
 */
typedef OesTrdCnfmT     OesTrdItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_TRD_ITEM                            \
        NULLOBJ_OES_TRD_CNFM
/* -------------------------           */


/**
 * 查询成交信息请求
 */
typedef struct _OesQryTrdReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryTrdFilterT    qryFilter;
} OesQryTrdReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRD_REQ                         \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_TRD_FILTER}


/**
 * 查询成交信息应答
 */
typedef struct _OesQryTrdRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 成交信息数组 */
    OesTrdItemT         qryItems[OES_MAX_TRD_ITEM_CNT_PER_PACK];
} OesQryTrdRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRD_RSP                         \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_TRD_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询客户资金信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户资金信息过滤条件
 */
typedef struct _OesQryCashAssetFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCashAssetFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CASH_ASSET_FILTER               \
        {0}, {0}, 0
/* -------------------------           */


/**
 * 客户资金信息内容
 */
typedef struct _OesCashAssetItem {
    __OES_CASH_ASSET_BASE_INFO_PKT;
    __OES_CASH_ASSET_EXT_INFO_PKT;
} OesCashAssetItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CASH_ASSET_ITEM                     \
        __NULLOBJ_OES_CASH_ASSET_BASE_INFO_PKT, \
        __NULLOBJ_OES_CASH_ASSET_EXT_INFO_PKT
/* -------------------------           */


/**
 * 查询客户资金信息请求
 */
typedef struct _OesQryCashAssetReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryCashAssetFilterT  qryFilter;
} OesQryCashAssetReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CASH_ASSET_REQ                  \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CASH_ASSET_FILTER}
/* -------------------------           */


/**
 * 查询客户资金信息应答
 */
typedef struct _OesQryCashAssetRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 客户资金信息数组 */
    OesCashAssetItemT   qryItems[OES_MAX_CASH_ASSET_ITEM_CNT_PER_PACK];
} OesQryCashAssetRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CASH_ASSET_RSP                  \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CASH_ASSET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询主柜资金信息相关结构体定义
 * =================================================================== */

/**
 * 主柜资金信息内容
 */
typedef struct _OesCounterCashItem {
    /** 资金账户代码 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 客户姓名 */
    char                custName[OES_CUST_NAME_MAX_LEN];
    /** 银行代码 */
    char                bankId[OES_BANK_NO_MAX_LEN];

    uint8               cashType;               /**< 资金账户类别 @see eOesCashTypeT */
    uint8               cashAcctStatus;         /**< 资金账户状态 @see eOesAcctStatusT */
    uint8               currType;               /**< 币种类型 @see eOesCurrTypeT */
    uint8               isFundTrsfDisabled;     /**< 出入金是否禁止标识 */
    uint8               __filler[4];            /**< 按64位对齐填充域 */

    int64               counterAvailableBal;    /**< 主柜可用余额，单位精确到元后四位，即1元 = 10000 */
    int64               counterDrawableBal;     /**< 主柜可取余额，单位精确到元后四位，即1元 = 10000 */
    int64               counterCashUpdateTime;  /**< 主柜资金更新时间 (seconds since the Epoch) */

    char                __reserve[32];          /**< 保留字段 */
} OesCounterCashItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_COUNTER_CASH_ITEM                   \
        {0}, {0}, {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 查询主柜资金信息请求
 */
typedef struct _OesQryCounterCashReq {
    /** 资金账号, 必输项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
} OesQryCounterCashReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COUNTER_CASH_REQ                \
        {0}
/* -------------------------           */


/**
 * 查询主柜资金信息应答
 */
typedef struct _OesQryCounterCashRsp {
    /** 主柜资金信息 */
    OesCounterCashItemT counterCashItem;
} OesQryCounterCashRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COUNTER_CASH_RSP                \
        {NULLOBJ_OES_COUNTER_CASH_ITEM}
/* -------------------------           */


/* ===================================================================
 * 查询股票持仓信息相关结构体定义
 * =================================================================== */

/**
 * 查询股票持仓信息过滤条件
 */
typedef struct _OesQryStkHoldingFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码  @see eOesMarketIdT */
    uint8               mktId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 产品类型 @see eOesProductTypeT */
    uint8               productType;
    /** 按64位对齐填充域 */
    uint8               __filler[5];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryStkHoldingFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STK_HOLDING_FILTER              \
        {0}, {0}, {0}, \
        0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询到的股票持仓信息内容
 */
typedef struct _OesStkHoldingItem {
    __OES_STK_HOLDING_BASE_INFO_PKT;
    __OES_STK_HOLDING_EXT_INFO_PKT;
} OesStkHoldingItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_STK_HOLDING_ITEM                    \
        __NULLOBJ_OES_STK_HOLDING_BASE_INFO_PKT, \
        __NULLOBJ_OES_STK_HOLDING_EXT_INFO_PKT
/* -------------------------           */


/**
 * 查询股票持仓信息请求
 */
typedef struct _OesQryStkHoldingReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryStkHoldingFilterT     qryFilter;
} OesQryStkHoldingReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STK_HOLDING_REQ                 \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_STK_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查询股票持仓信息应答
 */
typedef struct _OesQryStkHoldingRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 持仓信息数组 */
    OesStkHoldingItemT      qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryStkHoldingRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STK_HOLDING_RSP                 \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_STK_HOLDING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权持仓信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权持仓信息过滤条件
 */
typedef struct _OesQryOptHoldingFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码 @see eOesMarketIdT */
    uint8               mktId;
    /** 持仓类型 @see eOesOptPositionTypeT */
    uint8               positionType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptHoldingFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_FILTER              \
        {0}, {0}, {0}, \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询到的期权持仓信息内容
 */
typedef struct _OesOptHoldingItem {
    __OES_OPT_HOLDING_BASE_INFO_PKT;
    __OES_OPT_HOLDING_EXT_INFO_PKT;

    /** 交易所合约代码 */
    char                contractId[OES_CONTRACT_EXCH_ID_MAX_LEN];
    /** 期权合约简称 */
    char                contractSymbol[OES_SECURITY_NAME_MAX_LEN];
    /** 昨结算价 */
    int64               prevSettlPrice;
} OesOptHoldingItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_HOLDING_ITEM                    \
        __NULLOBJ_OES_OPT_HOLDING_BASE_INFO_PKT, \
        __NULLOBJ_OES_OPT_HOLDING_EXT_INFO_PKT, \
        {0}, {0}, 0
/* -------------------------           */


/**
 * 查询期权持仓信息请求
 */
typedef struct _OesQryOptHoldingReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryOptHoldingFilterT     qryFilter;
} OesQryOptHoldingReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_REQ                 \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查询期权持仓信息应答
 */
typedef struct _OesQryOptHoldingRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 持仓信息数组 */
    OesOptHoldingItemT      qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryOptHoldingRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_RSP                 \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_HOLDING_ITEM}}
/* -------------------------           */



/* ===================================================================
 * 查询客户信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户信息过滤条件
 */
typedef struct _OesQryCustFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCustFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CUST_FILTER                     \
        {0}, 0
/* -------------------------           */


/**
 * 客户信息内容
 */
typedef OesCustBaseInfoT    OesCustItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CUST_ITEM                           \
        NULLOBJ_OES_CUST_BASE_INFO
/* -------------------------           */


/**
 * 查询客户信息请求
 */
typedef struct _OesQryCustReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCustFilterT   qryFilter;
} OesQryCustReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CUST_REQ                        \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CUST_FILTER}
/* -------------------------           */


/**
 * 查询客户信息应答
 */
typedef struct _OesQryCustRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 客户信息数组 */
    OesCustItemT        qryItems[OES_MAX_CUST_ITEM_CNT_PER_PACK];
} OesQryCustRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CUST_RSP                        \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CUST_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询证券账户信息相关结构体定义
 * =================================================================== */

/**
 * 查询证券账户信息过滤条件
 */
typedef struct _OesQryInvAcctFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryInvAcctFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_INV_ACCT_FILTER                 \
        {0}, {0}, \
        0, {0}, 0
/* -------------------------           */


/**
 * 证券账户内容
 */
typedef struct _OesInvAcctItem {
    __OES_INV_ACCT_BASE_INFO_PKT;

    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
} OesInvAcctItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_INV_ACCT_ITEM                       \
        __NULLOBJ_OES_INV_ACCT_BASE_INFO_PKT, \
        {0}
/* -------------------------           */


/**
 * 查询证券账户信息请求
 */
typedef struct _OesQryInvAcctReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryInvAcctFilterT    qryFilter;
} OesQryInvAcctReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_INV_ACCT_REQ                    \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_INV_ACCT_FILTER}
/* -------------------------           */


/**
 * 查询证券账户信息应答
 */
typedef struct _OesQryInvAcctRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 证券账户信息数组 */
    OesInvAcctItemT     qryItems[OES_MAX_INV_ACCT_ITEM_CNT_PER_PACK];
} OesQryInvAcctRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_INV_ACCT_RSP                    \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_INV_ACCT_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询客户端总览信息相关结构体定义
 * =================================================================== */

/**
 * 股东账户总览信息内容
 */
typedef struct _OesInvAcctOverview {
    /** 股东账户代码 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 市场 @see eOesMarketIdT */
    uint8               mktId;

    /** 账户类型 @see eOesAcctTypeT */
    uint8               acctType;
    /** 账户状态 @see eOesAcctStatusT */
    uint8               status;
    /** 股东账户的所有者类型 @see eOesOwnerTypeT */
    uint8               ownerType;
    /** 期权投资者级别 @see eOesOptInvLevelT */
    uint8               optInvLevel;
    /** 是否禁止交易 (仅供API查询使用) */
    uint8               isTradeDisabled;
    /** 按64位对齐填充域 */
    uint8               __INV_ACCT_BASE_filler[2];

    /** 证券账户权限限制 @see eOesTradingLimitT */
    uint64              limits;
    /** 股东权限/客户权限 @see eOesTradingPermissionT */
    uint64              permissions;

    /** 席位号 */
    int32               pbuId;
    /** 主板权益 (新股/配股认购限额) */
    int32               subscriptionQuota;

    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];

    uint8               isValid;                /**< 股东账户是否有效标识 */
    uint8               __filler[3];            /**< 按64位对齐的填充域 */
    int32               kcSubscriptionQuota;    /**< 科创板权益 (新股/配股认购限额) */

    int32               trdOrdCnt;              /**< 当日累计有效交易类委托笔数统计 */
    int32               nonTrdOrdCnt;           /**< 当日累计有效非交易类委托笔数统计 */
    int32               cancelOrdCnt;           /**< 当日累计有效撤单笔数统计 */
    int32               oesRejectOrdCnt;        /**< 当日累计被OES拒绝的委托笔数统计 */
    int32               exchRejectOrdCnt;       /**< 当日累计被交易所拒绝的委托笔数统计 */
    int32               trdCnt;                 /**< 当日累计成交笔数统计 */

    char                __reserve[8];           /**< 备用字段 */
} OesInvAcctOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_INV_ACCT_OVERVIEW                   \
        {0}, 0, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, \
        {0}, \
        0, {0}, 0, \
        0, 0, 0, 0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 资金账户总览信息内容
 */
typedef struct _OesCashAcctOverview {
    /** 资金账户代码 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 银行代码 */
    char                bankId[OES_BANK_NO_MAX_LEN];

    uint8               isValid;                /**< 资金账户是否有效标识 */
    uint8               cashType;               /**< 资金账户类别 @see eOesCashTypeT */
    uint8               cashAcctStatus;         /**< 资金账户状态 @see eOesAcctStatusT */
    uint8               currType;               /**< 币种类型 @see eOesCurrTypeT */
    uint8               isFundTrsfDisabled;     /**< 出入金是否禁止标识 */
    uint8               __filler[3];            /**< 按64位对齐的填充域 */

    char                __reserve[8];           /**< 备用字段 */
} OesCashAcctOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CASH_ACCT_OVERVIEW                  \
        {0}, {0}, {0}, \
        0, 0, 0, 0, 0, {0}, \
        {0}
/* -------------------------           */


/**
 * 客户总览信息内容
 */
typedef struct _OesCustOverview {
    __OES_CUST_BASE_INFO_PKT;

    /** 客户姓名 */
    char                    custName[OES_CUST_NAME_MAX_LEN];

    OesCashAcctOverviewT    spotCashAcct;           /**< 普通资金账户信息 */
    OesCashAcctOverviewT    creditCashAcct;         /**< 信用资金账户信息 */
    OesCashAcctOverviewT    optionCashAcct;         /**< 衍生品资金账户信息 */

    OesInvAcctOverviewT     shSpotInvAcct;          /**< 上海现货股东账户信息 */
    OesInvAcctOverviewT     shOptionInvAcct;        /**< 上海衍生品股东账户信息 */
    OesInvAcctOverviewT     szSpotInvAcct;          /**< 深圳现货股东账户信息 */
    OesInvAcctOverviewT     szOptionInvAcct;        /**< 深圳衍生品股东账户信息 */

    char                    __reserve[8];           /**< 备用字段 */
} OesCustOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CUST_OVERVIEW                       \
        __NULLOBJ_OES_CUST_BASE_INFO_PKT, {0}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {0}
/* -------------------------           */


/**
 * 客户端总览信息内容
 */
typedef struct _OesClientOverview {
    int16               clientId;               /**< 客户端编号 */
    uint8               clientType;             /**< 客户端类型  @see eOesClientTypeT */
    uint8               clientStatus;           /**< 客户端状态  @see eOesClientStatusT */
    uint8               isApiForbidden;         /**< API禁用标识 */
    uint8               isBlockTrader;          /**< 是否大宗交易标识 */
    uint8               businessScope;          /**< 客户端适用的业务范围 @see eOesBusinessScopeT */
    uint8               __filler;               /**< 按64位对齐的填充域 */
    int64               logonTime;              /**< 客户端登录(委托接收服务)时间 */

    /** 客户端名称 */
    char                clientName[OES_CLIENT_NAME_MAX_LEN];
    /** 客户端说明 */
    char                clientMemo[OES_CLIENT_DESC_MAX_LEN];

    int32               sseStkPbuId;            /**< 上海现货/信用账户对应的PBU代码 */
    int32               sseOptPbuId;            /**< 上海衍生品账户对应的PBU代码 */
    uint8               sseQualificationClass;  /**< 上海股东账户的投资者适当性管理分类 @see eOesQualificationClassT */
    uint8               __filler2[7];           /**< 按64位对齐填充域 */

    int32               szseStkPbuId;           /**< 深圳现货/信用账户对应的PBU代码 */
    int32               szseOptPbuId;           /**< 深圳衍生品账户对应的PBU代码 */
    uint8               szseQualificationClass; /**< 深圳股东账户的投资者适当性管理分类 @see eOesQualificationClassT */
    uint8               __filler3[7];           /**< 按64位对齐填充域 */

    int32               currOrdConnected;       /**< 当前已连接的委托通道数量 */
    int32               currRptConnected;       /**< 当前已连接的回报通道数量 */
    int32               currQryConnected;       /**< 当前已连接的查询通道数量 */
    int32               maxOrdConnect;          /**< 委托通道允许的最大同时连接数量 */
    int32               maxRptConnect;          /**< 回报通道允许的最大同时连接数量 */
    int32               maxQryConnect;          /**< 查询通道允许的最大同时连接数量 */

    int32               ordTrafficLimit;        /**< 委托通道的流量控制 */
    int32               qryTrafficLimit;        /**< 查询通道的流量控制 */
    char                __reserve[8];           /**< 备用字段 */

    int32               associatedCustCnt;      /**< 客户端关联的客户数量 */
    int32               __filler4;              /**< 按64位对齐的填充域 */

    /** 客户端关联的客户列表 */
    OesCustOverviewT    custItems[OES_MAX_CUST_PER_CLIENT];
} OesClientOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CLIENT_OVERVIEW                     \
        0, 0, 0, 0, 0, 0, 0, 0, \
        {0}, {0}, \
        0, 0, 0, {0}, \
        0, 0, 0, {0}, \
        0, 0, 0, 0, 0, 0, \
        0, 0, {0}, \
        0, 0, \
        {{NULLOBJ_OES_CUST_OVERVIEW}}
/* -------------------------           */


/* ===================================================================
 * 查询客户佣金信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户佣金信息过滤条件
 */
typedef struct _OesQryCommissionRateFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 证券类别, 可选项。如无需此过滤条件请使用 OES_SECURITY_TYPE_UNDEFINE
     * @see eOesSecurityTypeT
     */
    uint8               securityType;
    /**
     * 买卖类型, 可选项。如无需此过滤条件请使用 OES_BS_TYPE_UNDEFINE
     * @see eOesBuySellTypeT
     */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint8               __filler[5];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCommissionRateFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_FILTER          \
        {0}, 0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 客户佣金信息内容定义
 */
typedef struct _OesCommissionRateItem {
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券代码 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场 @see eOesMarketIdT */
    uint8               mktId;
    /** 证券类别 @see eOesSecurityTypeT */
    uint8               securityType;
    /** 证券子类别 @see eOesSubSecurityTypeT */
    uint8               subSecurityType;
    /** 买卖类型 @see eOesBuySellTypeT */
    uint8               bsType;

    /** 费用标识 @see eOesFeeTypeT */
    uint8               feeType;
    /** 币种 @see eOesCurrTypeT */
    uint8               currType;
    /** 计算模式 @see eOesCalcFeeModeT */
    uint8               calcFeeMode;
    /** 按64位对齐填充域 */
    uint8               __filler;

    /** 费率, 单位精确到千万分之一, 即费率0.02% = 2000 */
    int64               feeRate;
    /** 最低费用, 大于0时有效 (单位：万分之一元) */
    int32               minFee;
    /** 最高费用, 大于0时有效 (单位：万分之一元) */
    int32               maxFee;
} OesCommissionRateItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_COMMISSION_RATE_ITEM                \
        {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询客户佣金信息请求
 */
typedef struct _OesQryCommissionRateReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryCommissionRateFilterT qryFilter;
} OesQryCommissionRateReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_COMMISSION_RATE_FILTER}
/* -------------------------           */


/**
 * 查询客户佣金信息应答
 */
typedef struct _OesQryCommissionRateRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 客户佣金信息数组 */
    OesCommissionRateItemT  qryItems[OES_MAX_COMMS_RATE_ITEM_CNT_PER_PACK];
} OesQryCommissionRateRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_COMMISSION_RATE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询出入金流水信息相关结构体定义
 * =================================================================== */

/**
 * 查询出入金流水信息过滤条件
 */
typedef struct _OesQryFundTransferSerialFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 出入金流水号, 可选项 */
    int32               clSeqNo;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 按64位对齐填充域 */
    uint8               __filler[3];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryFundTransferSerialFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_FILTER     \
        {0}, {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询出入金流水信息应答
 */
typedef OesFundTrsfReportT      OesFundTransferSerialItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_FUND_TRANSFER_SERIAL_ITEM           \
        NULLOBJ_OES_FUND_TRSF_REPORT
/* -------------------------           */


/**
 * 查询出入金流水信息请求
 */
typedef struct _OesQryFundTransferSerialReq {
    /** 查询请求消息头 */
    OesQryReqHeadT                  reqHead;
    /** 查询过滤条件 */
    OesQryFundTransferSerialFilterT qryFilter;
} OesQryFundTransferSerialReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_REQ        \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_FILTER}
/* -------------------------           */


/**
 * 查询出入金流水信息应答
 */
typedef struct _OesQryFundTransferSerialRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT              rspHead;
    /** 出入金流水信息数组 */
    OesFundTransferSerialItemT  qryItems[OES_MAX_FUND_TRSF_ITEM_CNT_PER_PACK];
} OesQryFundTransferSerialRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_RSP        \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_FUND_TRANSFER_SERIAL_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询新股配号、中签信息相关结构体定义
 * =================================================================== */

/**
 * 查询新股配号、中签信息过滤条件
 */
typedef struct _OesQryLotWinningFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 查询记录类型, 可选项。如无需此过滤条件请使用 OES_LOT_TYPE_UNDEFINE
     * @see eOesLotTypeT
     */
    uint8               lotType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 查询起始日期 (格式为 YYYYMMDD) */
    int32               startDate;
    /** 查询结束日期 (格式为 YYYYMMDD) */
    int32               endDate;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryLotWinningFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_LOT_WINNING_FILTER              \
        {0}, {0}, \
        0, 0, {0}, \
        0, 0, 0
/* -------------------------           */


/**
 * 新股配号、中签信息内容
 */
typedef OesLotWinningBaseInfoT      OesLotWinningItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_LOT_WINNING_ITEM                    \
        NULLOBJ_OES_LOT_WINNING_BASE_INFO
/* -------------------------           */


/**
 * 查询新股认购、中签信息请求
 */
typedef struct _OesQryLotWinningReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryLotWinningFilterT     qryFilter;
} OesQryLotWinningReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_LOT_WINNING_REQ                 \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_LOT_WINNING_FILTER}
/* -------------------------           */


/**
 * 查询新股配号、中签信息应答
 */
typedef struct _OesQryLotWinningRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 新股认购、中签信息数组 */
    OesLotWinningItemT      qryItems[OES_MAX_LOG_WINNING_ITEM_CNT_PER_PACK];
} OesQryLotWinningRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_LOT_WINNING_RSP                 \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_LOT_WINNING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询证券发行信息相关结构体定义
 * =================================================================== */

/**
 * 查询证券发行信息过滤条件
 */
typedef struct _OesQryIssueFilter {
    /** 证券发行代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;

    /**
     * 产品类型, 默认类型为 OES_PRODUCT_TYPE_IPO
     * @see eOesProductTypeT
     */
    uint8               productType;

    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryIssueFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ISSUE_FILTER                    \
        {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 证券发行信息内容
 */
typedef OesIssueBaseInfoT   OesIssueItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ISSUE_ITEM                          \
        NULLOBJ_OES_ISSUE_BASE_INFO
/* -------------------------           */


/**
 * 查询证券发行信息请求
 */
typedef struct _OesQryIssueReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryIssueFilterT  qryFilter;
} OesQryIssueReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ISSUE_REQ                       \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ISSUE_FILTER}
/* -------------------------           */


/**
 * 查询证券发行信息应答
 */
typedef struct _OesQryIssueRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 证券发行信息数组 */
    OesIssueItemT       qryItems[OES_MAX_ISSUE_ITEM_CNT_PER_PACK];
} OesQryIssueRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ISSUE_RSP                       \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ISSUE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询现货产品信息相关结构体定义
 * =================================================================== */

/**
 * 查询现货产品信息过滤条件
 */
typedef struct _OesQryStockFilter {
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 证券子类别  @see eOesSubSecurityTypeT */
    uint8               subSecurityType;
    /** 按64位对齐填充域 */
    uint8               __filler[5];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryStockFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STOCK_FILTER                    \
        {0}, 0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 现货产品信息内容
 */
typedef OesStockBaseInfoT       OesStockItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_STOCK_ITEM                          \
        NULLOBJ_OES_STOCK_BASE_INFO
/* -------------------------           */


/**
 * 查询现货产品信息请求
 */
typedef struct _OesQryStockReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryStockFilterT  qryFilter;
} OesQryStockReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STOCK_REQ                       \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_STOCK_FILTER}
/* -------------------------           */


/**
 * 查询现货产品信息应答
 */
typedef struct _OesQryStockRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 现货产品信息数组 */
    OesStockItemT       qryItems[OES_MAX_STOCK_ITEM_CNT_PER_PACK];
} OesQryStockRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STOCK_RSP                       \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_STOCK_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询ETF申赎产品信息相关结构体定义
 * =================================================================== */

/**
 * 查询ETF申赎产品信息过滤条件
 */
typedef struct _OesQryEtfFilter {
    /** ETF基金申赎代码, 可选项 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];

    /**
     * ETF基金市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryEtfFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_FILTER                      \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * ETF申赎产品信息内容
 */
typedef OesEtfBaseInfoT     OesEtfItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ETF_ITEM                            \
        NULLOBJ_OES_ETF_BASE_INFO
/* -------------------------           */


/**
 * 查询ETF申赎产品信息请求
 */
typedef struct _OesQryEtfReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryEtfFilterT    qryFilter;
} OesQryEtfReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_REQ                         \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ETF_FILTER}
/* -------------------------           */


/**
 * 查询ETF申赎产品信息应答
 */
typedef struct _OesQryEtfRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** ETF申赎产品信息数组 */
    OesEtfItemT         qryItems[OES_MAX_ETF_ITEM_CNT_PER_PACK];
} OesQryEtfRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_RSP                         \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ETF_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询ETF成份证券信息相关结构体定义
 * =================================================================== */

/**
 * 查询ETF成份证券信息过滤条件
 */
typedef struct _OesQryEtfComponentFilter {
    /** ETF基金申赎代码 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];

    /**
     * ETF基金市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               fundMktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryEtfComponentFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_FILTER            \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * ETF基金成份证券信息内容
 */
typedef struct _OesEtfComponentItem {
    __OES_ETF_COMPONENT_BASE_INFO_PKT;

    /** 成份证券名称 */
    char                securityName[OES_SECURITY_NAME_MAX_LEN];
    /** 预留的备用字段 */
    char                __reserve[96];
} OesEtfComponentItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ETF_COMPONENET_ITEM                 \
        __NULLOBJ_OES_ETF_COMPONENT_BASE_INFO_PKT, \
        {0}, {0}
/* -------------------------           */


/**
 * 查询ETF基金成份证券信息请求
 */
typedef struct _OesQryEtfComponentReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryEtfComponentFilterT   qryFilter;
} OesQryEtfComponentReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_REQ               \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ETF_COMPONENT_FILTER}
/* -------------------------           */


/**
 * 查询ETF基金成份证券信息应答
 */
typedef struct _OesQryEtfComponentRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** ETF基金成份证券信息数组 */
    OesEtfComponentItemT
                        qryItems[OES_MAX_ETF_COMPONENT_ITEM_CNT_PER_PACK];
} OesQryEtfComponentRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_RSP               \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ETF_COMPONENET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权产品信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权产品信息过滤条件
 */
typedef struct _OesQryOptionFilter {
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptionFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPTION_FILTER                   \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * 期权产品信息内容
 */
typedef OesOptionBaseInfoT      OesOptionItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPTION_ITEM                         \
        NULLOBJ_OES_OPTION_BASE_INFO
/* -------------------------           */


/**
 * 查询期权产品信息请求
 */
typedef struct _OesQryOptionReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryOptionFilterT qryFilter;
} OesQryOptionReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPTION_REQ                      \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPTION_FILTER}
/* -------------------------           */


/**
 * 查询期权产品信息应答
 */
typedef struct _OesQryOptionRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 期权产品信息数组 */
    OesOptionItemT      qryItems[OES_MAX_OPTION_ITEM_CNT_PER_PACK];
} OesQryOptionRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPTION_RSP                      \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPTION_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权标的持仓信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权标的持仓信息过滤条件
 */
typedef struct _OesQryOptUnderlyingHoldingFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 标的证券代码, 可选项 */
    char                underlyingSecurityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码  @see eOesMarketIdT */
    uint8               mktId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               underlyingSecurityType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptUnderlyingHoldingFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_UNDERLYING_HOLDING_FILTER   \
        {0}, {0}, {0}, \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询到的期权标的持仓信息内容
 */
typedef OesOptUnderlyingHoldingBaseInfoT    OesOptUnderlyingHoldingItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_UNDERLYING_HOLDING_ITEM         \
        NULLOBJ_OES_OPT_UNDERLYING_HOLDING_BASE_INFO
/* -------------------------           */


/**
 * 查询期权标的持仓信息请求
 */
typedef struct _OesQryOptUnderlyingHoldingReq {
    /** 查询请求消息头 */
    OesQryReqHeadT                      reqHead;
    /** 查询过滤条件 */
    OesQryOptUnderlyingHoldingFilterT   qryFilter;
} OesQryOptUnderlyingHoldingReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_UNDERLYING_HOLDING_REQ      \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_UNDERLYING_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查询期权标的持仓信息应答
 */
typedef struct _OesQryOptUnderlyingHoldingRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 期权标的持仓信息数组 */
    OesOptUnderlyingHoldingItemT
                        qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryOptUnderlyingHoldingRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_UNDERLYING_HOLDING_RSP      \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_UNDERLYING_HOLDING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权限仓额度信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权限仓额度信息过滤条件
 */
typedef struct _OesQryOptPositionLimitFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 标的证券代码, 可选项 */
    char                underlyingSecurityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码  @see eOesMarketIdT */
    uint8               mktId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               underlyingSecurityType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptPositionLimitFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_POSITION_LIMIT_FILTER       \
        {0}, {0}, {0}, \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询到的期权限仓额度信息内容
 */
typedef struct _OesOptPositionLimitItem {
    /** 股东账户代码 (不带'888'编码的原始股东账户代码) */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 标的证券代码 */
    char                underlyingSecurityId[OES_SECURITY_ID_MAX_LEN];
    /** 市场代码 (衍生品市场) @see eOesMarketIdT */
    uint8               mktId;

    /** 标的市场代码 @see eOesMarketIdT */
    uint8               underlyingMktId;
    /** 标的证券类型 @see eOesSecurityTypeT */
    uint8               underlyingSecurityType;
    /** 标的证券子类型 @see eOesSubSecurityTypeT */
    uint8               underlyingSubSecurityType;
    /** 按64位对齐的填充域 */
    uint8               __filler1[4];

    /** 权利仓限额 */
    int32               longPositionLimit;
    /** 总持仓限额 */
    int32               totalPositionLimit;
    /** 单日买入开仓限额 */
    int32               dailyBuyOpenLimit;
    /** 按64位对齐的填充域 */
    int32               __filler2;

    /** 日初权利仓持仓数量 (单位: 张) */
    int32               originalLongQty;
    /** 日初义务仓持仓数量 (单位: 张) */
    int32               originalShortQty;
    /** 日初备兑义务仓持仓数量 (单位: 张) */
    int32               originalCoveredQty;

    /** 未占用的权利仓限额 */
    int32               availableLongPositionLimit;
    /** 未占用的总持仓限额 */
    int32               availableTotalPositionLimit;
    /** 未占用的单日买入开仓限额 */
    int32               availableDailyBuyOpenLimit;

    /** 预留的备用字段 */
    char                __reserve[8];
} OesOptPositionLimitItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_POSITION_LIMIT_ITEM             \
        {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 查询期权限仓额度信息请求
 */
typedef struct _OesQryOptPositionLimitReq {
    /** 查询请求消息头 */
    OesQryReqHeadT                      reqHead;
    /** 查询过滤条件 */
    OesQryOptPositionLimitFilterT       qryFilter;
} OesQryOptPositionLimitReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_POSITION_LIMIT_REQ          \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_POSITION_LIMIT_FILTER}
/* -------------------------           */


/**
 * 查询期权限仓额度信息应答
 */
typedef struct _OesQryOptPositionLimitRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 期权标的持仓信息数组 */
    OesOptPositionLimitItemT
                        qryItems[OES_MAX_OPT_UNDERLYING_ITEM_CNT_PER_PACK];
} OesQryOptPositionLimitRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_POSITION_LIMIT_RSP          \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_POSITION_LIMIT_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询限购消息相关结构体定义
 * =================================================================== */

/**
 * 查询期权限购额度信息过滤条件
 */
typedef struct _OesQryOptPurchaseLimitFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码 (不带'888'编码的原始股东账户代码), 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码 (衍生品市场), 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptPurchaseLimitFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_PURCHASE_LIMIT_FILTER       \
        {0}, {0}, 0, {0}, \
        0
/* -------------------------           */


/**
 * 期权限购额度信息内容
 */
typedef struct _OesOptPurchaseLimitItem {
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 股东账户代码 (不带'888'编码的原始股东账户代码) */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 市场代码 (衍生品市场) @see eOesMarketIdT */
    uint8               mktId;
    /** 客户类别 @see eOesCustTypeT */
    uint8               custType;
    /** 按64位对齐的填充数据 */
    uint8               __filler[6];

    /** 限购额度/套保额度 */
    int64               purchaseLimit;
    /** 日初占用的期权限购额度 */
    int64               originalUsedPurchaseAmt;
    /** 日中累计开仓占用的期权限购额度 */
    int64               totalOpenPurchaseAmt;
    /** 当前挂单冻结的期权限购额度 */
    int64               frzPurchaseAmt;
    /** 日中累计平仓释放的期权限购额度 */
    int64               totalClosePurchaseAmt;
    /** 可用限购额度/套保额度 */
    int64               availablePurchaseLimit;
} OesOptPurchaseLimitItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_PURCHASE_LIMIT_ITEM             \
        {0}, {0}, {0}, 0, 0, {0}, \
        0, 0, 0, 0, 0, 0
/* -------------------------           */



/**
 * 查询到的期权行权指派信息内容
 */
typedef OesOptionExerciseAssignBaseT    OesOptExerciseAssignItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_EXERCISE_ASSIGN_ITEM            \
        NULLOBJ_OES_OPTION_EXERCISE_ASSIGN_BASE
/* -------------------------           */


/**
 * 查询期权限购额度信息请求
 */
typedef struct _OesQryOptPurchaseLimitReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryOptPurchaseLimitFilterT
                            qryFilter;
} OesQryOptPurchaseLimitReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_PURCHASE_LIMIT_REQ          \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_PURCHASE_LIMIT_FILTER}
/* -------------------------           */


/**
 * 查询期权限购额度信息应答
 */
typedef struct _OesQryOptPurchaseLimitRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 通知消息数组 */
    OesOptPurchaseLimitItemT
                            qryItems[OES_MAX_OPT_PURCHASE_LIMIT_ITEM_CNT_PER_PACK];
} OesQryOptPurchaseLimitRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_PURCHASE_LIMIT_RSP          \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_PURCHASE_LIMIT_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权行权指派信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权行权指派信息过滤条件
 */
typedef struct _OesQryOptExerciseAssignFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 期权合约代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码 @see eOesMarketIdT */
    uint8               mktId;
    /** 持仓类型 @see eOesOptPositionTypeT */
    uint8               positionType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptExerciseAssignFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_EXERCISE_ASSIGN_FILTER      \
        {0}, {0}, {0}, \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询期权行权指派信息请求
 */
typedef struct _OesQryOptExerciseAssignReq {
    /** 查询请求消息头 */
    OesQryReqHeadT                      reqHead;
    /** 查询过滤条件 */
    OesQryOptExerciseAssignFilterT      qryFilter;
} OesQryOptExerciseAssignReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_EXERCISE_ASSIGN_REQ         \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_EXERCISE_ASSIGN_FILTER}
/* -------------------------           */


/**
 * 查询期权行权指派信息应答
 */
typedef struct _OesQryOptExerciseAssignRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 期权行权指派信息数组 */
    OesOptExerciseAssignItemT
                        qryItems[OES_MAX_EXERCISE_ASSIGN_ITEM_CNT_PER_PACK];
} OesQryOptExerciseAssignRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_EXERCISE_ASSIGN_RSP         \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_EXERCISE_ASSIGN_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询当前交易日信息相关结构体定义
 * =================================================================== */

/**
 * 查询当前交易日信息应答
 */
typedef struct _OesQryTradingDayRsp {
    /** 交易日 */
    int32               tradingDay;
    /** 按64位对齐填充域 */
    int32               __filler;
} OesQryTradingDayRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRADING_DAY_RSP                 \
        0, 0
/* -------------------------           */


/* ===================================================================
 * 查询市场状态信息相关结构体定义
 * =================================================================== */

/**
 * 查询市场状态信息过滤条件
 */
typedef struct _OesQryMarketStateFilter {
    /**
     * 交易所代码 (可选项, 为 0 则匹配所有交易所)
     * @see eOesExchangeIdT
     */
    uint8               exchId;

    /**
     * 交易平台代码 (可选项, 为 0 则匹配所有交易平台)
     * @see eOesPlatformIdT
     */
    uint8               platformId;

    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryMarketStateFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_MARKET_STATE_FILTER             \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 市场状态信息内容
 *
 */
typedef OesMarketStateInfoT     OesMarketStateItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_MARKET_STATE_ITEM                   \
        NULLOBJ_OES_MARKET_STATE_INFO
/* -------------------------           */


/**
 * 查询市场状态信息请求
 */
typedef struct _OesQryMarketStateReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryMarketStateFilterT
                            qryFilter;
} OesQryMarketStateReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_MARKET_STATE_REQ                \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_MARKET_STATE_FILTER}
/* -------------------------           */


/**
 * 查询市场状态信息应答
 */
typedef struct _OesQryMarketStateRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 市场状态信息数组 */
    OesMarketStateItemT     qryItems[OES_MAX_MKT_STATE_ITEM_CNT_PER_PACK];
} OesQryMarketStateRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_MARKET_STATE_RSP                \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_MARKET_STATE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询通知消息相关结构体定义
 * =================================================================== */

/**
 * 查询通知消息过滤条件
 */
typedef struct _OesQryNotifyInfoFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 通知消息等级 @see eOesNotifyLevelT */
    uint8               notifyLevel;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryNotifyInfoFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_NOTIFY_INFO_FILTER              \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * 通知消息内容
 */
typedef OesNotifyBaseInfoT  OesNotifyInfoItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_NOTIFY_INFO_ITEM                    \
        NULLOBJ_OES_NOTIFY_BASE_INFO
/* -------------------------           */


/**
 * 查询通知消息请求
 */
typedef struct _OesQryNotifyInfoReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryNotifyInfoFilterT
                            qryFilter;
} OesQryNotifyInfoReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_NOTIFY_INFO_REQ                 \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_NOTIFY_INFO_FILTER}
/* -------------------------           */


/* ===================================================================
 * 查询券商参数信息相关结构体定义
 * =================================================================== */

/**
 * 券商参数信息内容
 */
typedef struct _OesBrokerParamsInfo {
    /** 券商名称 */
    char                brokerName[OES_BROKER_NAME_MAX_LEN];
    /** 券商联系电话 */
    char                brokerPhone[OES_BROKER_PHONE_MAX_LEN];
    /** 券商网址 */
    char                brokerWebsite[OES_BROKER_WEBSITE_MAX_LEN];

    /** 当前API协议版本号 */
    char                apiVersion[OES_VER_ID_MAX_LEN];
    /** 为兼容协议而添加的填充域 */
    char               __filler1[8];
    /** API兼容的最低协议版本号 */
    char                apiMinVersion[OES_VER_ID_MAX_LEN];
    /** 为兼容协议而添加的填充域 */
    char               __filler2[8];
    /** 客户端最新的版本号 */
    char                clientVersion[OES_VER_ID_MAX_LEN];
    /** 为兼容协议而添加的填充域 */
    char               __filler3[8];

    /** 允许客户端修改密码的开始时间 (HHMMSSsss) */
    int32               changePwdLimitTime;
    /** 客户端密码允许的最小长度 */
    int32               minClientPasswordLen;
    /**
     * 客户端密码强度级别
     * 密码强度范围[0~4]，密码含有字符种类(大写字母、小写字母、数字、有效符号)的个数
     */
    int32               clientPasswordStrength;
    /** 服务端业务范围 @see eOesBusinessScopeT */
    uint32              businessScope;

    /** 预留的备用字段 */
    char                __reserve[64];

    /** 业务范围扩展信息 */
    union {
        struct {
            int32       withdrawLineRatio;      /**< 投资人出金提取线 (万分比) */
            int32       __filler;               /**< 按64位对齐填充域 */
        } optionExt;

        char            __extInfo[192];         /**< 占位用的扩展信息 */
    };
} OesBrokerParamsInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_BROKER_PARAMS_INFO                  \
        {0}, {0}, {0}, \
        {0}, {0}, {0}, {0}, {0}, {0}, \
        0, 0, 0, 0, \
        {0}, {{0, 0}}

/**
* 查询券商参数信息应答
*/
typedef struct _OesQryBrokerParamsInfoRsp {
   OesBrokerParamsInfoT    brokerParams;
} OesQryBrokerParamsInfoRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_BROKER_PARAMS_INFO_RSP          \
       {NULLOBJ_OES_BROKER_PARAMS_INFO}
/* -------------------------           */


/**
 * 查询通知消息应答
 */
typedef struct _OesQryNotifyInfoRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 通知消息数组 */
    OesNotifyInfoItemT      qryItems[OES_MAX_NOTIFY_INFO_ITEM_CNT_PER_PACK];
} OesQryNotifyInfoRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_NOTIFY_INFO_RSP                 \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_NOTIFY_INFO_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询周边应用升级配置信息相关结构体定义
 * =================================================================== */

/**
 * 查询周边应用升级配置信息应答
 */
typedef struct _OesQryApplUpgradeInfoRsp {
    OesApplUpgradeInfoT     applUpgradeInfo;
} OesQryApplUpgradeInfoRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_APPL_UPGRADE_INFO_RSP          \
        {NULLOBJ_OES_APPL_UPGRADE_INFO}
/* -------------------------           */


/* ===================================================================
 * 统一的查询消息定义
 * =================================================================== */

/**
 * 统一的查询请求消息定义
 */
typedef union _OesQryReqMsg {
    OesQryOrdReqT                   qryOrd;                     /**< 查询委托信息请求 */
    OesQryTrdReqT                   qryTrd;                     /**< 查询成交信息请求 */
    OesQryCashAssetReqT             qryCashAsset;               /**< 查询客户资金信息请求 */
    OesQryStkHoldingReqT            qryStkHolding;              /**< 查询股票持仓信息请求 */
    OesQryOptHoldingReqT            qryOptHolding;              /**< 查询期权持仓信息请求 */
    OesQryCustReqT                  qryCust;                    /**< 查询客户信息请求 */
    OesQryInvAcctReqT               qryInvAcct;                 /**< 查询证券账户请求 */
    OesQryCommissionRateReqT        qryComms;                   /**< 查询客户佣金信息请求 */
    OesQryFundTransferSerialReqT    qryFundTrsf;                /**< 查询出入金信息请求 */
    OesQryLotWinningReqT            qryLotWinning;              /**< 查询新股配号、中签信息请求 */
    OesQryIssueReqT                 qryIssue;                   /**< 查询证券发行信息请求 */
    OesQryStockReqT                 qryStock;                   /**< 查询现货产品信息请求 */
    OesQryEtfReqT                   qryEtf;                     /**< 查询ETF申赎产品信息请求 */
    OesQryEtfComponentReqT          qryEtfComponent;            /**< 查询ETF基金成份证券信息请求 */
    OesQryOptionReqT                qryOption;                  /**< 查询期权产品信息请求 */
    OesQryMarketStateReqT           qryMktState;                /**< 查询市场状态信息请求 */
    OesQryNotifyInfoReqT            qryNotifyInfo;              /**< 查询通知消息请求 */
    OesQryCounterCashReqT           qryCounterCash;             /**< 查询主柜资金信息请求 */
    OesQryOptPositionLimitReqT      qryOptPositionLimit;        /**< 查询期权限仓额度信息请求 */
    OesQryOptPurchaseLimitReqT      qryOptPurchaseLimit;        /**< 查询期权限购额度信息请求 */
    OesQryOptUnderlyingHoldingReqT  qryOptUnderlyingHolding;    /**< 查询期权标的持仓信息请求 */
    OesQryOptExerciseAssignReqT     qryOptExerciseAssign;       /**< 查询期权行权指派信息请求 */
} OesQryReqMsgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_REQ_MSG                         \
        {NULLOBJ_OES_QRY_ORD_REQ}
/* -------------------------           */


/**
 * 统一的查询应答消息定义
 */
typedef union _OesQryRspMsg {
    OesQryOrdRspT                   ordRsp;                     /**< 查询委托信息应答 */
    OesQryTrdRspT                   trdRsp;                     /**< 查询成交信息应答 */
    OesQryCashAssetRspT             cashAssetRsp;               /**< 查询客户资金信息应答 */
    OesQryStkHoldingRspT            stkHoldingRsp;              /**< 查询股票持仓信息应答 */
    OesQryOptHoldingRspT            optHoldingRsp;              /**< 查询期权持仓信息应答 */
    OesQryCustRspT                  custRsp;                    /**< 查询客户信息应答 */
    OesQryInvAcctRspT               invAcctRsp;                 /**< 查询证券账户应答 */
    OesQryCommissionRateRspT        commsRateRsp;               /**< 查询客户佣金信息应答 */
    OesQryFundTransferSerialRspT    fundTrsfRsp;                /**< 查询出入金流水信息应答 */
    OesQryLotWinningRspT            lotWinningRsp;              /**< 查询新股配号、中签信息应答 */
    OesQryIssueRspT                 issueRsp;                   /**< 查询证券发行信息应答 */
    OesQryStockRspT                 stockRsp;                   /**< 查询现货产品信息应答 */
    OesQryEtfRspT                   etfRsp;                     /**< 查询ETF申赎产品信息应答 */
    OesQryEtfComponentRspT          etfComponentRsp;            /**< 查询ETF基金成份证券信息应答 */
    OesQryOptionRspT                optionRsp;                  /**< 查询期权产品信息应答 */
    OesQryTradingDayRspT            tradingDay;                 /**< 查询当前交易日信息应答 */
    OesQryMarketStateRspT           mktStateRsp;                /**< 查询市场状态信息应答 */
    OesQryNotifyInfoRspT            notifyInfoRsp;              /**< 查询通知消息应答 */
    OesClientOverviewT              clientOverview;             /**< 客户端总览信息 */
    OesQryCounterCashRspT           counterCashRsp;             /**< 客户主柜资金信息 */
    OesQryOptPositionLimitRspT      optPositionLimitRsp;        /**< 查询期权限仓额度信息应答 */
    OesQryOptPurchaseLimitRspT      optPurchaseLimitRsp;        /**< 查询期权限购额度信息应答 */
    OesQryOptUnderlyingHoldingRspT  optUnderlyingHoldingRsp;    /**< 查询期权标的持仓信息应答 */
    OesQryOptExerciseAssignRspT     optExerciseAssignRsp;       /**< 查询期权行权指派信息应答 */
    OesQryBrokerParamsInfoRspT      brokerParamsRsp;            /**< 查询券商参数信息应答 */
    OesQryApplUpgradeInfoRspT       applUpgradeRsp;             /**< 周边应用升级信息 */
} OesQryRspMsgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_RSP_MSG                         \
        {NULLOBJ_OES_QRY_ORD_RSP}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_QRY_PACKETS_H */
