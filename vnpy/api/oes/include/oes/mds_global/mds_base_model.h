/*
 * Copyright 2020 the original author or authors.
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
 * @file    mds_base_model.h
 *
 * MDS系统的基础领域模型(数据结构)定义
 *
 * - 行情数据的字段命名风格说明:
 *   - 以大写字母开头的字段, 都是直接来源于交易所的数据;
 *   - 以小写字母开头的字段, 是额外增加的或者经过转换的数据;
 *   - 以双下划线开头的字段, 是系统的内部字段
 *
 * @version 0.8.12      2016/09/13
 * @version 0.12.8      2017/03/07
 *          - 删除独立的 MdsMktDataSnapshotEntryMetaT 结构体,
 *            将字段整合到 MdsMktDataSnapshotHeadT 中, 并删除原 meta.priceUnit (价格单位) 字段
 *          - 重命名 MdsMktDataSnapshotEntryT -> MdsL1SnapshotBodyT
 *          - 重命名 MdsIndexDataSnapshotEntryT -> MdsIndexSnapshotBodyT
 *          - 重命名 MdsStockDataSnapshotEntryT -> MdsStockSnapshotBodyT
 *          - 重命名 MdsStockSnapshotBodyT.PreCloseIOPV -> NAV
 *          - 重定义 MdsStockSnapshotBodyT.PriceLevel[5] -> BidLevels[5] + OfferLevels[5]
 *              - PriceLevel\[(\w+)\].BuyPrice -> BidLevels[\1].Price
 *              - PriceLevel\[(\w+)\].BuyVolume -> BidLevels[\1].OrderQty
 *              - PriceLevel\[(\w+)\].SellPrice -> OfferLevels[\1].Price
 *              - PriceLevel\[(\w+)\].SellVolume -> OfferLevels[\1].OrderQty
 *          - 重命名 MdsStockSnapshotBodyT.TradeVolume -> TotalVolumeTraded
 *          - 重命名 MdsIndexSnapshotBodyT.TradeVolume -> TotalVolumeTraded
 *          - 删除 MdsStockSnapshotBodyT.MDStreamID, MdsIndexSnapshotBodyT.MDStreamID 字段
 *          - 为'市场状态'和'证券实时状态'消息添加 __exchSendingTime, __mdsRecvTime 字段,
 *            以方便比对实际的行情延时
 * @version 0.12.8.2    2017/05/16
 *          - 添加 '逐笔数据丢失消息(MdsL2TickLostT)', 以通知下游系统逐笔数据(逐笔成交/逐笔
 *            委托)发生了数据丢失, 并且无法重建, 将放弃这些丢失的逐笔数据
 *          - 调整证券实时状态结构体中延迟打点时间戳字段的字段位置, 将这些字段调整到结构体的末尾,
 *            以方便客户端兼容处理
 * @version 0.12.9.7    2017/07/12
 *          - 不再对外发布逐笔丢失消息(MDS_MSGTYPE_L2_TICK_LOST), 该消息已废弃
 * @version 0.15.4.1    2017/09/07
 *          - 默认开启用于统计延时的打点信息, 并将打点信息的时间戳类型改为 timeval32 (STimeval32T) 类型,
 *            同时将行情推送的打点信息, 从消息头迁移到消息体中 (__pushingTime)
 * @version 0.15.5.10   2018/05/20
 *          - 行情结构体中增加内部频道号字段 (兼容之前版本), 该字段仅内部使用, 前端不需要关心和处理
 * @version 0.15.5.11   2018/06/01
 *          - 扩大Level2增量更新消息中最大已变更价位列表和委托明细的最大数量, 修复因为支持
 *            同时变更的价位数量不足, 导致部分巨幅波动场景下会丢失价位信息的BUG
 * @version 0.15.7.6_RC1 2018/11/06
 *          - 重命名 L1快照体(MdsL1SnapshotBodyT) 的初始化宏名称
 *            - NULLOBJ_MDS_MKT_DATA_SNAPSHOT_BODY => NULLOBJ_MDS_L1_SNAPSHOT_BODY
 * @version 0.15.8_RC3  2019/01/14
 *          - 删除已经废弃的虚拟集合竞价消息的消息定义和数据类型定义
 *          - 重命名 securityType => mdProductType, 以避免与交易端的证券类型混淆
 *              - securityType => mdProductType
 *              - eMdsSecurityTypeT => eMdsMdProductTypeT
 * @version 0.15.8_u1   2019/03/22
 *          - 交易所代码的枚举类型中增加 '未定义的交易所代码 (MDS_EXCH_UNDEFINE)'
 * @version 0.15.8_u6   2019/05/06
 *          - 调整快照头 MdsMktDataSnapshotHeadT 中的内部字段定义, 将 __origTickSeq 字段
 *            拆分为 __origTickSeq + __lastUpdateTime 两个字段 (内部使用的字段, 协议保持兼容)
 * @version 0.15.9      2019/03/12
 *          - 为了支持科创板, 扩展证券静态信息(MdsStockStaticInfoT)的结构体定义, 增加如下字段:
 *              - 限价买数量上限 (lmtBuyMaxQty)
 *              - 限价买数量下限 (lmtBuyMinQty)
 *              - 限价卖数量上限 (lmtSellMaxQty)
 *              - 限价卖数量下限 (lmtSellMinQty)
 *              - 市价买数量上限 (mktBuyMaxQty)
 *              - 市价买数量下限 (mktBuyMinQty)
 *              - 市价卖数量上限 (mktSellMaxQty)
 *              - 市价卖数量下限 (mktSellMinQty)
 *          - 扩大证券业务开关的最大数量, 该修改可能会对之前版本的API造成影响, 兼容性问题如下:
 *              - 会影响到证券实时状态消息的延迟计算, 旧版本会读取到无效的打点时间
 *          - 调整行情数据类型(mdStreamType, eMdsMdStreamTypeT)的取值, 使其可以标识出快
 *            照行情的具体数据类型
 *              - 该修改会存在兼容性问题, 客户端程序可以通过编译错误来识别需要调整的地方 (如
 *                果没有编译错误就不需要调整)
 *              - 行情数据类型的取值将尽量与消息类型保持一致, 但以下类型比较特殊
 *                  - 深交所成交量统计指标
 *                  - 上交所 Level1 行情快照-债券
 *                  - 上交所 Level1 行情快照-基金
 *          - 宏定义 '用户名最大长度 (MDS_MAX_USERNAME_LEN)' 从 40 调整为 32
 * @version 0.15.9.1    2019/06/24
 *          - 为逐笔成交/逐笔委托/市场状态消息/证券实时状态这4个行情消息补充"原始行情数据来
 *            源 (__origMdSource)" 字段
 * @version 0.15.9.3    2019/10/16
 *          - 调整证券信息(MdsStockStaticInfoT)的结构体定义
 *              - 增加 '总股本(outstandingShare)' 和 '流通股数量(publicFloatShare)' 字段
 *          - 行情数据类型(eMdsMdStreamTypeT)中新增类型
 *              - 深交所国证指数快照行情 (MDS_MD_STREAM_TYPE_SZSE_CN_INDEX)
 *          - 调整指数快照行情中 '今收盘指数(CloseIdx)' 字段的注释信息, 深交所指数快照行情也将提供收盘指数
 * @version 0.15.10.5   2020/04/10
 *          - 废弃快照头中的内部字段 __lastUpdateTime, 取值固定为0 (内部使用的字段, 协议保持兼容)
 *          - 调整快照行情中 '昨日收盘价(PrevClosePx)' 字段的注释信息, 不再通过该字段推送昨结算价 (深交所期权快照中没有结算价字段)
 * @version 0.15.10.6   2020/04/19
 *          - 将延迟统计相关的时间戳字段升级为纳秒级时间戳 (内部使用的字段, 协议保持兼容, STimeval32T => STimespec32T)
 * @version 0.15.11     2020/05/29
 *          - '证券静态信息(MdsStockStaticInfoT)' 中增加如下字段:
 *              - 币种 (currType)
 *              - 投资者适当性管理分类 (qualificationClass)
 *              - 证券状态 (securityStatus)
 *              - 证券属性 (securityAttribute), 保留字段
 *              - 连续停牌标识 (suspFlag)
 *              - 是否支持当日回转交易 (isDayTrading)
 *              - 是否注册制 (isRegistration)
 *              - 是否为融资标的 (isCrdMarginTradeUnderlying)
 *              - 是否为融券标的 (isCrdShortSellUnderlying)
 *              - 是否为融资融券担保品 (isCrdCollateral)
 *              - 是否尚未盈利 (isNoProfit)
 *              - 是否存在投票权差异 (isWeightedVotingRights)
 *              - 是否具有协议控制框架 (isVie)
 *              - 限价买入单位 (lmtBuyQtyUnit)
 *              - 限价卖出单位 (lmtSellQtyUnit)
 *              - 市价买入单位 (mktBuyQtyUnit)
 *              - 市价卖出单位 (mktSellQtyUnit)
 *              - 面值 (parValue), 兼容旧版'parPrice'字段
 *              - 连续交易时段的有效竞价范围限制类型 (auctionLimitType)
 *              - 连续交易时段的有效竞价范围基准价类型 (auctionReferPriceType)
 *              - 连续交易时段的有效竞价范围涨跌幅度 (auctionUpDownRange)
 *              - 上市日期 (listDate)
 *              - 到期日期 (maturityDate)
 *              - 基础证券代码 (underlyingSecurityId)
 *              - 证券长名称 (securityLongName)
 *              - 证券英文名称 (securityEnglishName)
 *              - ISIN代码 (securityIsinCode)
 * @version 0.15.11.3   2020/06/26
 *          - 统一涨跌停价格字段的名称 (协议保持兼容)
 *              - upperLimitPrice, 涨停价
 *              - lowerLimitPrice, 跌停价
 * @version 0.15.11.9   2020/08/28
 *          - 复用快照头中已废弃的内部字段 __lastUpdateTime, 并重命名为 __directSourceId (内部使用的字段, 协议保持兼容)
 * @version 0.15.11.12  2020/09/30
 *          - 新增 证券属性定义(eOesSecurityAttributeT) 枚举类型
 *          - '证券静态信息(MdsStockStaticInfoT)' 中启用 证券属性 (securityAttribute) 字段
 * @version 0.15.12     2021/03/11
 *          - '上交所Level2快照行情的增量更新消息 (MdsL2StockSnapshotIncrementalT)' 中增加如下字段:
 *              - 最高价 (HighPx)
 *              - 最低价 (LowPx)
 *              - @note 协议发生变化, 如果需要使用增量更新消息, 就必须升级到最新版本 (通常不会也不建议使用该消息)
 *          - 调整 '逐笔成交 (MdsL2TradeT)' 结构体定义
 *              - 调整内部字段 '内部频道号 (__channelNo)' 的定义顺序, 如果使用了该字段就
 *                需要升级到最新版本
 *              - 删除内部字段 '对应的原始行情的序列号 (__origTickSeq)'
 *              - 增加上交所逐笔委托相关的字段:
 *                  - 业务序列号 (SseBizIndex, 仅适用于上交所)
 *              - @note 协议保持兼容, 只是上述两个内部字段有变化
 *          - 调整 '逐笔委托 (MdsL2OrderT)' 结构体定义
 *              - 调整内部字段 '内部频道号 (__channelNo)' 的定义顺序, 如果使用了该字段就需要升级到最新版本
 *              - 删除内部字段 '对应的原始行情的序列号 (__origTickSeq)'
 *              - 增加上交所逐笔委托相关的字段:
 *                  - 业务序列号 (SseBizIndex, 仅适用于上交所)
 *                  - 原始订单号 (SseOrderNo, 仅适用于上交所)
 *              - @note 协议保持兼容, 只是上述两个内部字段有变化
 *          - 新增枚举类型 '上交所逐笔委托的订单类型 (eMdsL2SseOrderTypeT)'
 *
 * @since   2016/02/11
 */


#ifndef _MDS_BASE_MODEL_H
#define _MDS_BASE_MODEL_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 预编译宏处理
 * =================================================================== */

/* 默认开启用于统计延时的打点信息 */
#if ! defined (_MDS_DISABLE_LATENCY_STATS) \
        && ! defined (_MDS_ENABLE_LATENCY_STATS)
#   define  _MDS_ENABLE_LATENCY_STATS           1
#endif
/* -------------------------           */


/* ===================================================================
 * 常量定义 (宏定义)
 * =================================================================== */

/** 每次的行情订阅请求中可以同时指定的最大订阅产品数量 (可以通过追加订阅的方式订阅更多的产品) */
#define MDS_MAX_SECURITY_CNT_PER_SUBSCRIBE      (4000)
/** 对于沪/深两市的期权产品, 限制对每个市场最多允许同时订阅 2000 只产品 */
#define MDS_MAX_OPTION_CNT_TOTAL_SUBSCRIBED     (2000)

/** 用户名最大长度 */
#define MDS_MAX_USERNAME_LEN                    (32)
/** 密码最大长度 */
#define MDS_MAX_PASSWORD_LEN                    (40)
/** 客户端标签最大长度 */
#define MDS_CLIENT_TAG_MAX_LEN                  (32)
/** 协议版本号的最大长度 */
#define MDS_VER_ID_MAX_LEN                      (32)
/** 测试请求标识符的最大长度 */
#define MDS_MAX_TEST_REQ_ID_LEN                 (32)

/** 点分十进制的IPv4, 字符串的最大长度 */
#define MDS_MAX_IP_LEN                          (16)
/** MAC地址字符串的最大长度 */
#define MDS_MAX_MAC_LEN                         (20)
/** MAC地址字符串的最大长度(按64位对齐的长度) */
#define MDS_MAX_MAC_ALGIN_LEN                   (24)
/** 设备序列号字符串的最大长度 */
#define MDS_MAX_DRIVER_ID_LEN                   (21)
/** 设备序列号字符串的最大长度(按64位对齐的长度) */
#define MDS_MAX_DRIVER_ID_ALGIN_LEN             (24)

/** 证券代码长度(C6/C8) */
#define MDS_MAX_INSTR_CODE_LEN                  (9)
/** 实际的股票产品代码长度 */
#define MDS_REAL_STOCK_CODE_LEN                 (6)
/** 实际的期权产品代码长度 */
#define MDS_REAL_OPTION_CODE_LEN                (8)
/** 允许带.SH/.SZ后缀的产品代码的最大长度 */
#define MDS_MAX_POSTFIXED_INSTR_CODE_LEN        (12)

/** 证券名称最大长度 */
#define MDS_MAX_SECURITY_NAME_LEN               (40)
/** 证券长名称长度 */
#define MDS_MAX_SECURITY_LONG_NAME_LEN          (80)
/** 证券英文名称长度 */
#define MDS_MAX_SECURITY_ENGLISH_NAME_LEN       (48)
/** 证券ISIN代码长度 */
#define MDS_MAX_SECURITY_ISIN_CODE_LEN          (16)

/** 期权合约交易代码长度 */
#define MDS_MAX_CONTRACT_EXCH_ID_LEN            (24)
/** 期权合约交易代码实际长度 */
#define MDS_REAL_CONTRACT_EXCH_ID_LEN           (19)

/** 发送时间字段(YYYYMMDD-HH:mm:SS.sss (*C21))的最大长度 */
#define MDS_MAX_SENDING_TIME_LEN                (22)
/** 发送时间字段(YYYYMMDD-HH:mm:SS.sss (*C21))的实际有效数据长度 */
#define MDS_REAL_SENDING_TIME_LEN               (21)

/** 交易日期字段(YYYYMMDD (*C8))的最大长度 */
#define MDS_MAX_TRADE_DATE_LEN                  (9)
/** 交易日期字段(YYYYMMDD (*C8))的实际有效数据长度 */
#define MDS_REAL_TRADE_DATE_LEN                 (8)

/** 最新更新时间字段(HHMMSSss (*C8))的最大长度 */
#define MDS_MAX_UPDATE_TIME_LEN                 (9)
/** 最新更新时间字段(HHMMSSss (*C8))的实际有效数据长度 */
#define MDS_REAL_UPDATE_TIME_LEN                (8)

/** 全市场行情状态字段(*C8)的最大长度 */
#define MDS_MAX_TRADING_SESSION_ID_LEN          (9)
/** 全市场行情状态字段(*C8)的实际有效数据长度 */
#define MDS_REAL_TRADING_SESSION_ID_LEN         (8)

/** 产品实时阶段及标志(C8/C4)的最大长度 */
#define MDS_MAX_TRADING_PHASE_CODE_LEN          (9)
/** 产品实时阶段及标志(C8/C4)的实际有效数据长度 */
#define MDS_REAL_TRADING_PHASE_CODE_LEN         (8)

/** 证券状态字段(深交所证券实时状态消息 C8)的最大长度 */
#define MDS_MAX_FINANCIAL_STATUS_LEN            (9)
/** 证券状态字段(深交所证券实时状态消息 C8)的实际有效数据长度 */
#define MDS_REAL_FINANCIAL_STATUS_LEN           (8)

/** 证券业务开关的最大数量(深交所证券实时状态消息) */
#define MDS_MAX_SECURITY_SWITCH_CNT             (40)

/** 统一的价格单位 */
#define MDS_UNIFIED_PRICE_UNIT                  (10000)
/** 统一的金额单位 */
#define MDS_UNIFIED_MONEY_UNIT                  (10000)

/** 总成交金额的金额单位 (上交所的总成交金额精度原本为2位, 但在此统一整合为4位精度) */
#define MDS_TOTAL_VALUE_TRADED_UNIT             MDS_UNIFIED_MONEY_UNIT
/** 指数的价格单位 */
#define MDS_INDEX_PRICE_UNIT                    MDS_UNIFIED_PRICE_UNIT
/** 股票的价格单位 (上交所的股票价格精度原本为3位, 但在此统一整合为4位精度) */
#define MDS_STOCK_PRICE_UNIT                    MDS_UNIFIED_PRICE_UNIT
/** 期权的价格单位 */
#define MDS_OPTION_PRICE_UNIT                   MDS_UNIFIED_PRICE_UNIT

/** 逐笔委托中委托价格的最大值 (如果逐笔委托中的委托价格超出该值, 则将赋值为该值) */
#define MDS_MAX_ORDER_PRICE                     (1999999999)

/** 股票代码的最大范围 */
#define MDS_MAX_STOCK_ID_SCOPE                  (1000000)
/** 期权代码的最大范围 */
#define MDS_MAX_OPTION_ID_SCOPE                 (100000000)

/** 发送方/接收方代码的最大长度 */
#define MDS_MAX_COMP_ID_LEN                     (32)

/** 周边应用废弃版本数目的最大个数 */
#define MDS_APPL_DISCARD_VERSION_MAX_COUNT      (5)
/** 周边应用升级协议名称的最大长度 */
#define MDS_APPL_UPGRADE_PROTOCOL_MAX_LEN       (32)
/* -------------------------           */


/* ===================================================================
 * Level2 相关的常量定义
 * =================================================================== */

/** Level2增量更新的价位列表最大数量 */
#define MDS_MAX_L2_PRICE_LEVEL_INCREMENTS       (40)

/** Level2披露的买一／卖一委托明细最大数量 */
#define MDS_MAX_L2_DISCLOSE_ORDERS_CNT          (50)

/** Level2增量更新的委托明细最大数量 */
#define MDS_MAX_L2_DISCLOSE_ORDERS_INCREMENTS   (152)
/* -------------------------           */


/* ===================================================================
 * 常量定义 (枚举类型定义)
 * =================================================================== */

/**
 * 交易所代码
 */
typedef enum _eMdsExchangeId {
    MDS_EXCH_UNDEFINE                   = 0,    /**< 未定义的交易所代码 */
    MDS_EXCH_SSE                        = 1,    /**< 交易所-上交所 */
    MDS_EXCH_SZSE                       = 2,    /**< 交易所-深交所 */
    __MAX_MDS_EXCH,

    __MAX_MDS_EXCH_ALIGNED4             = 4,    /**< 交易所代码最大值 (按4字节对齐的大小) */
    __MAX_MDS_EXCH_ALIGNED8             = 8     /**< 交易所代码最大值 (按8字节对齐的大小) */
} eMdsExchangeIdT;


/**
 * 消息来源
 */
typedef enum _eMdsMsgSource {
    MDS_MSGSRC_UNDEFINED                = 0,    /**< 消息来源-未定义 */
    MDS_MSGSRC_EZEI_TCP                 = 1,    /**< 消息来源-EzEI(TCP) */
    MDS_MSGSRC_EZEI_UDP                 = 2,    /**< 消息来源-EzEI(UDP) */

    MDS_MSGSRC_VDE_LEVEL2               = 3,    /**< 消息来源-SSE-VDE-LEVEL2 */
    MDS_MSGSRC_VDE_LEVEL1               = 4,    /**< 消息来源-SSE-VDE-LEVEL1-FAST */
    MDS_MSGSRC_VDE_LEVEL2_REBUILD       = 103,  /**< 消息来源-SSE-VDE-LEVEL2-逐笔重建 */

    MDS_MSGSRC_SZSE_MDGW_BINARY         = 5,    /**< 消息来源-SZSE-MDGW-Binary */
    MDS_MSGSRC_SZSE_MDGW_STEP           = 6,    /**< 消息来源-SZSE-MDGW-STEP */
    MDS_MSGSRC_SZSE_MDGW_REBUILD        = 105,  /**< 消息来源-SZSE-MDGW-Binary-逐笔重建 */

    MDS_MSGSRC_MDS_TCP                  = 7,    /**< 消息来源-MDS(TCP, 仅内部使用, 实盘下不会出现) */
    MDS_MSGSRC_MDS_UDP                  = 8,    /**< 消息来源-MDS(UDP, 仅内部使用, 实盘下不会出现) */
    MDS_MSGSRC_FILE_MKTDT               = 9,    /**< 消息来源-文件(mktdt) */

    MDS_MSGSRC_SSE_MDGW_BINARY          = 10,   /**< 消息来源-SSE-MDGW-Binary */
    MDS_MSGSRC_SSE_MDGW_STEP            = 11,   /**< 消息来源-SSE-MDGW-STEP */
    __MAX_MDS_MSGSRC,

    /** 消息来源-SZSE-MDGW-Binary @deprecated 已过时, 请使用 MDS_MSGSRC_SZSE_MDGW_BINARY */
    MDS_MSGSRC_MDGW_BINARY              = MDS_MSGSRC_SZSE_MDGW_BINARY,
    /** 消息来源-SZSE-MDGW-STEP @deprecated 已过时, 请使用 MDS_MSGSRC_SZSE_MDGW_STEP */
    MDS_MSGSRC_MDGW_STEP                = MDS_MSGSRC_SZSE_MDGW_STEP
} eMdsMsgSourceT;


/**
 * 行情类别 (和交易端的产品类型不同, 行情数据中的产品类型只是用于区分是现货行情还是衍生品行情)
 */
typedef enum _eMdsMdProductType {
    MDS_MD_PRODUCT_TYPE_STOCK           = 1,    /**< 股票(基金/债券) */
    MDS_MD_PRODUCT_TYPE_INDEX           = 2,    /**< 指数 */
    MDS_MD_PRODUCT_TYPE_OPTION          = 3,    /**< 期权 */
    __MAX_MDS_MD_PRODUCT_TYPE,

    /* @deprecated 以下定义已过时, 为保持兼容而暂时保留 */
    MDS_SECURITY_TYPE_STOCK             = MDS_MD_PRODUCT_TYPE_STOCK,
    MDS_SECURITY_TYPE_INDEX             = MDS_MD_PRODUCT_TYPE_INDEX,
    MDS_SECURITY_TYPE_OPTION            = MDS_MD_PRODUCT_TYPE_OPTION,
    __MAX_MDS_SECURITY_TYPE             = __MAX_MDS_MD_PRODUCT_TYPE
} eMdsMdProductTypeT;


/**
 * 行情数据类型 (仅适用于快照行情, 用于标识 Level1/Level2 快照行情的具体数据类型)
 *
 * @note    行情数据类型的取值将尽量与消息类型保持一致, 但以下类型比较特殊
 *          - 深交所成交量统计指标快照行情 (消息类型为指数快照)
 *          - 深交所国证指数快照行情 (消息类型为指数快照)
 *          - 上交所 Level1 行情快照-债券 (消息类型为 Level1 行情快照)
 *          - 上交所 Level1 行情快照-基金 (消息类型为 Level1 行情快照)
 * @see     eMdsMsgTypeT
 */
typedef enum _eMdsMdStreamType {
    /** Level1 市场行情快照 (10/0x0A) */
    MDS_MD_STREAM_TYPE_L1_SNAPSHOT      = 10,
    /** Level1/Level2 指数行情快照 (11/0x0B) */
    MDS_MD_STREAM_TYPE_INDEX            = 11,
    /** Level1/Level2 期权行情快照 (12/0x0C) */
    MDS_MD_STREAM_TYPE_OPTION           = 12,

    /** 深交所 Level1/Level2 成交量统计指标 (15/0x0F, 结构与指数行情相同) */
    MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS = 15,
    /** 上交所 Level1 行情快照-债券 (16/0x10, 仅适用于上交所Level-1行情) */
    MDS_MD_STREAM_TYPE_SSE_L1_BOND      = 16,
    /** 上交所 Level1 行情快照-基金 (17/0x11, 仅适用于上交所Level-1行情) */
    MDS_MD_STREAM_TYPE_SSE_L1_FUND      = 17,

    /** Level2 市场行情快照 (20/0x14) */
    MDS_MD_STREAM_TYPE_L2_SNAPSHOT      = 20,
    /** Level2 委托队列快照 (买一/卖一前五十笔) (21/0x15) */
    MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT
                                        = 21,

    /** Level2 快照行情的增量更新消息 (24/0x18, 仅适用于上交所) */
    MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL
                                        = 24,
   /** Level2 委托队列快照的增量更新消息 (25/0x19, 仅适用于上交所) */
    MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL
                                        = 25,
    /** Level2 市场总览消息 (26/0x1A, 仅适用于上交所) */
    MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW
                                        = 26,

    /* 扩展的特殊行情数据类型 */
    /** 深交所国证指数快照行情 (51/0x33, 结构与指数快照相同) */
    MDS_MD_STREAM_TYPE_SZSE_CN_INDEX    = 51,

    __MAX_MDS_MD_STREAM_TYPE,

    /* @deprecated 以下定义已过时, 为保持兼容而暂时保留 */
    MDS_MD_STREAM_TYPE_BOND             = MDS_MD_STREAM_TYPE_SSE_L1_BOND,
    MDS_MD_STREAM_TYPE_FUND             = MDS_MD_STREAM_TYPE_SSE_L1_FUND,
    MDS_MD_STREAM_TYPE_OTHERS           = MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW
} eMdsMdStreamTypeT;


/**
 * 行情数据级别 (Level1 / Level2)
 */
typedef enum _eMdsMdLevel {
    MDS_MD_LEVEL_0                      = 0,    /**< 未设置 */
    MDS_MD_LEVEL_1                      = 1,    /**< Level-1 行情 */
    MDS_MD_LEVEL_2                      = 2,    /**< Level-2 行情 */
    __MAX_MDS_MD_LEVEL
} eMdsMdLevelT;


/**
 * Level2增量更新消息的价位运算 (1=Add, 2=Update, 3=Delete)
 */
typedef enum _eMdsL2PriceLevelOperator {
    MDS_L2_PX_OPERATOR_ADD              = 1,    /**< L2价位运算 - Add */
    MDS_L2_PX_OPERATOR_UPDATE           = 2,    /**< L2价位运算 - Update */
    MDS_L2_PX_OPERATOR_DELETE           = 3,    /**< L2价位运算 - Delete */
    __MAX_MDS_L2_PX_OPERATOR
} eMdsL2PriceLevelOperatorT;


/**
 * Level2逐笔成交的成交类别
 * - 仅适用于深交所 ('4'=撤销, 'F'=成交)
 * - 对于上交所, 将固定取值为 'F'(成交)
 */
typedef enum _eMdsL2TradeExecType {
    MDS_L2_TRADE_EXECTYPE_CANCELED      = '4',  /**< L2执行类型 - 已撤销 */
    MDS_L2_TRADE_EXECTYPE_TRADE         = 'F'   /**< L2执行类型 - 已成交 */
} eMdsL2TradeExecTypeT;


/**
 * Level2逐笔成交的内外盘标志
 * - 仅适用于上交所 ('B'=外盘,主动买, 'S'=内盘,主动卖, 'N'=未知)
 * - 对于深交所, 将固定取值为 'N'(未知)
 */
typedef enum _eMdsL2TradeBSFlag {
    MDS_L2_TRADE_BSFLAG_BUY             = 'B',  /**< L2内外盘标志 - 外盘,主动买 */
    MDS_L2_TRADE_BSFLAG_SELL            = 'S',  /**< L2内外盘标志 - 内盘,主动卖 */
    MDS_L2_TRADE_BSFLAG_UNKNOWN         = 'N'   /**< L2内外盘标志 - 未知 */
} eMdsL2TradeBSFlagT;


/**
 * Level2逐笔委托的买卖方向 ('1'=买 '2'=卖 'G'=借入 'F'=出借)
 */
typedef enum _eMdsL2OrderSideT {
    MDS_L2_ORDER_SIDE_BUY               = '1',  /**< L2买卖方向 - 买 */
    MDS_L2_ORDER_SIDE_SELL              = '2',  /**< L2买卖方向 - 卖 */
    MDS_L2_ORDER_SIDE_BORROW            = 'G',  /**< L2买卖方向 - 借入 (仅适用于深交所) */
    MDS_L2_ORDER_SIDE_LEND              = 'F'   /**< L2买卖方向 - 出借 (仅适用于深交所) */
} eMdsL2OrderSideT;


/**
 * 深交所逐笔委托的订单类型
 */
typedef enum _eMdsL2OrderType {
    MDS_L2_ORDER_TYPE_MKT               = '1',  /**< 深交所订单类型 - 市价 */
    MDS_L2_ORDER_TYPE_LMT               = '2',  /**< 深交所订单类型 - 限价 */
    MDS_L2_ORDER_TYPE_SAMEPARTY_BEST    = 'U'   /**< 深交所订单类型 - 本方最优 */
} eMdsL2OrderTypeT;


/**
 * 上交所逐笔委托的订单类型
 */
typedef enum _eMdsL2SseOrderType {
    MDS_L2_SSE_ORDER_TYPE_ADD           = 'A',  /**< 上交所订单类型 - 增加 (即: 新订单) */
    MDS_L2_SSE_ORDER_TYPE_DELETE        = 'D'   /**< 上交所订单类型 - 删除 (即: 撤单) */
} eMdsL2SseOrderTypeT;


/**
 * 客户端类型定义 (内部使用)
 */
typedef enum _eMdsClientType {
    MDS_CLIENT_TYPE_UNDEFINED           = 0,    /**< 客户端类型-未定义 */
    MDS_CLIENT_TYPE_INVESTOR            = 1,    /**< 普通投资人 */
    MDS_CLIENT_TYPE_VIRTUAL             = 2     /**< 虚拟账户 (仅开通行情, 不可交易) */
} eMdsClientTypeT;


/**
 * 客户端状态定义 (内部使用)
 */
typedef enum _eMdsClientStatus {
    MDS_CLIENT_STATUS_UNACTIVATED       = 0,    /**< 未激活 (不加载) */
    MDS_CLIENT_STATUS_ACTIVATED         = 1,    /**< 已激活 (正常加载) */
    MDS_CLIENT_STATUS_PAUSE             = 2,    /**< 已暂停 (正常加载, 不可交易) */
    MDS_CLIENT_STATUS_SUSPENDED         = 3,    /**< 已挂起 (不加载) */
    MDS_CLIENT_STATUS_CANCELLED         = 4     /**< 已注销 (不加载) */
} eMdsClientStatusT;
/* -------------------------           */


/* ===================================================================
 * Level1 行情消息定义
 * =================================================================== */

/**
 * 市场状态消息(MsgType=h)定义 (仅适用于上交所, 深交所行情中没有该数据)
 */
typedef struct _MdsTradingSessionStatusMsg {
    uint8               exchId;                 /**< 交易所代码(沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/指数/期权) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重复的行情 (供内部使用, 小于0 表示数据倒流) */
    uint8               __origMdSource;         /**< 原始行情数据来源 @see eMdsMsgSourceT */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 通过拆解SendingTime得到, 并非官方数据) */
    int32               updateTime;             /**< 行情时间 (HHMMSSsss, 交易所时间, 通过拆解SendingTime得到, 并非官方数据) */
    int32               __exchSendingTime;      /**< 交易所发送时间 (HHMMSSsss) */
    int32               __mdsRecvTime;          /**< MDS接收到时间 (HHMMSSsss) */

    int32               TotNoRelatedSym;        /**< 最大产品数目 (包括指数) */

    /**
     * 全市场行情状态 (*C8)
     * 该字段为 8 位字符串,左起每位表示特定的含义,无定义则填空格。
     * 第 0 位: ‘S’表示全市场启动期间(开市前), ‘T’表示全市场处于交易期间 (含中间休市), ‘E’表示全市场处于闭市期间。
     * 第 1 位: ‘1’表示开盘集合竞价结束标志, 未结束取‘0’。
     * 第 2 位: ‘1’表示市场行情闭市标志, 未闭市取‘0’。
     */
    char                TradingSessionID[MDS_MAX_TRADING_SESSION_ID_LEN];

    uint8               __filler3[3];           /**< 按64位对齐的填充域 */
    uint32              __dataVersion;          /**< 行情数据的更新版本号 (当__isRepeated!=0时, 该值仅作为参考值) */
    uint64              __origTickSeq;          /**< 对应的原始行情的序列号(供内部使用) */

#if defined (_MDS_ENABLE_LATENCY_STATS) || defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
    /** 消息原始接收时间 (从网络接收到数据的最初时间) */
    STimespec32T        __origNetTime;
#endif
#if defined (_MDS_ENABLE_LATENCY_STATS)
    /** 消息实际接收时间 (开始解码等处理之前的时间) */
    STimespec32T        __recvTime;
    /** 消息采集处理完成时间 */
    STimespec32T        __collectedTime;
    /** 消息加工处理完成时间 */
    STimespec32T        __processedTime;
    /** 消息推送时间 (写入推送缓存以后, 实际网络发送之前) */
    STimespec32T        __pushingTime;
#endif

} MdsTradingSessionStatusMsgT;


/* 结构体初始化值的尾部填充字段定义 */
#if defined (_MDS_ENABLE_LATENCY_STATS)
# define    __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER             \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#elif defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
# define    __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER             \
            , {0, 0}
#else
# define    __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER
#endif


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG                          \
        NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG2(0, 0)


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG2(exchId, mdSource)       \
        (exchId), 0, 0, (mdSource), \
        0, 0, 0, 0, 0, \
        {0}, \
        {0}, 0, 0 \
        __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER
/* -------------------------           */


/**
 * 证券实时状态定义 (仅适用于深交所, 上交所行情中没有该数据)
 */
typedef struct _MdsSecurityStatusMsg {
    uint8               exchId;                 /**< 交易所代码(沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/指数/期权) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重复的行情 (供内部使用, 小于0 表示数据倒流) */
    uint8               __origMdSource;         /**< 原始行情数据来源 @see eMdsMsgSourceT */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 通过拆解数据生成时间OrigTime得到) */
    int32               updateTime;             /**< 行情时间 (HHMMSSsss, 交易所时间, 通过拆解数据生成时间OrigTime得到) */
    int32               __exchSendingTime;      /**< 交易所发送时间 (HHMMSSsss, 目前获取不到深交所的发送时间, 固定为 0) */
    int32               __mdsRecvTime;          /**< MDS接收到时间 (HHMMSSsss) */

    int32               instrId;                /**< 证券代码 (转换为整数类型的证券代码) */

    /** 证券代码 C6 / C8 (如: '000001' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 证券状态 (C8)
     * A=上市公司早间披露提示
     * B=上市公司午间披露提示
     */
    char                FinancialStatus[MDS_MAX_FINANCIAL_STATUS_LEN];

    uint8               __filler2;              /**< 按64位对齐的填充域 */
    uint8               __channelNo;            /**< 内部频道号 (供内部使用, 取值范围{1,2,4,8}) */
    uint32              __dataVersion;          /**< 行情数据的更新版本号 (当__isRepeated!=0时, 该值仅作为参考值) */
    uint64              __origTickSeq;          /**< 对应的原始行情的序列号(供内部使用) */

    int32               NoSwitch;               /**< 开关个数 */
    int32               __filler4;              /**< 按64位对齐的填充域 */

    /**
     * 证券业务开关列表
     * 业务开关列表为定长数组, 数组的下标位置对应于各个业务开关, 业务开关说明如下:
     *  -  1: 融资买入, 适用于融资标的证券
     *  -  2: 融券卖出, 适用于融券标的证券
     *  -  3: 申购, 适用于 ETF/LOF 等开放式基金, 对于黄金 ETF 是指现金申购
     *  -  4: 赎回, 适用于 ETF/LOF 等开放式基金, 对于黄金 ETF 是指现金赎回开关
     *  -  5: 认购, 适用于网上发行认购代码
     *  -  6: 转股, 适用于处于转股回售期的可转债
     *  -  7: 回售, 适用于处于转股回售期的可转债
     *  -  8: 行权, 适用于处于行权期的权证或期权
     *  - 10: 买开仓, 适用于期权等衍生品
     *  - 11: 卖开仓, 适用于期权等衍生品
     *  - 12: 黄金ETF实物申购, 适用于黄金 ETF
     *  - 13: 黄金ETF实物赎回, 适用于黄金 ETF
     *  - 14: 预受要约, 适用于处于要约收购期的股票
     *  - 15: 解除要约, 适用于处于要约收购期的股票
     *  - 18: 转股撤单, 适用于处于转股回售期的可转债
     *  - 19: 回售撤单, 适用于处于转股回售期的可转债
     *  - 20: 质押, 适用于质押式回购可质押入库证券
     *  - 21: 解押, 适用于质押式回购可质押入库证券
     *  - 22: 表决权, 适用于优先股
     *  - 23: 股票质押式回购, 适用于可开展股票质押式回购业务的证券
     *  - 24: 实时分拆, 适用于分级基金
     *  - 25: 实时合并, 适用于分级基金
     *  - 26: 备兑开仓, 适用于期权等衍生品
     *  - 27: 做市商报价, 适用于期权等支持做市商报价的证券
     *  - 28: 港股通整手买
     *  - 29: 港股通整手卖
     *  - 30: 港股通零股买
     *  - 31: 港股通零股卖
     *  - 32: 期权普通转备兑仓
     *  - 33: 期权备兑转普通仓
     */
    struct {
        /** 业务开关的使能标志 (0 未启用, 1 启用) */
        uint8           switchFlag;

        /** 开关状态 (0 关闭, 1 开启) */
        uint8           switchStatus;
    } switches[MDS_MAX_SECURITY_SWITCH_CNT];

#if defined (_MDS_ENABLE_LATENCY_STATS) || defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
    /** 消息原始接收时间 (从网络接收到数据的最初时间) */
    STimespec32T        __origNetTime;
#endif
#if defined (_MDS_ENABLE_LATENCY_STATS)
    /** 消息实际接收时间 (开始解码等处理之前的时间) */
    STimespec32T        __recvTime;
    /** 消息采集处理完成时间 */
    STimespec32T        __collectedTime;
    /** 消息加工处理完成时间 */
    STimespec32T        __processedTime;
    /** 消息推送时间 (写入推送缓存以后, 实际网络发送之前) */
    STimespec32T        __pushingTime;
#endif

} MdsSecurityStatusMsgT;


/* 结构体初始化值的尾部填充字段定义 */
#if defined (_MDS_ENABLE_LATENCY_STATS)
# define    __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER                    \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#elif defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
# define    __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER                    \
            , {0, 0}
#else
# define    __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER
#endif


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_SECURITY_STATUS_MSG                                 \
        NULLOBJ_MDS_SECURITY_STATUS_MSG2(0, 0)


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_SECURITY_STATUS_MSG2(exchId, mdSource)              \
        (exchId), 0, 0, (mdSource), \
        0, 0, 0, 0, 0, \
        {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, \
        { \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
        } \
        __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER
/* -------------------------           */


/* ===================================================================
 * Level1 快照行情定义
 * =================================================================== */

/**
 * 价位信息定义
 */
typedef struct _MdsPriceLevelEntry {
    int32               Price;                  /**< 委托价格 */
    int32               NumberOfOrders;         /**< 价位总委托笔数 (Level1不揭示该值, 固定为0) */
    int64               OrderQty;               /**< 委托数量 (上交所债券的数量单位为手) */
} MdsPriceLevelEntryT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_PRICE_LEVEL_ENTRY                                   \
        0, 0, 0
/* -------------------------           */


/**
 * Level1/Level2 快照行情(证券行情全幅消息)的消息头定义
 */
typedef struct _MdsMktDataSnapshotHead {
    uint8               exchId;                 /**< 交易所代码(沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/指数/期权) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重复的行情 (内部使用, 小于0表示数据倒流) */
    uint8               __origMdSource;         /**< 原始行情数据来源 @see eMdsMsgSourceT */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 8位整型数值) */
    int32               updateTime;             /**< 行情时间 (HHMMSSsss, 交易所时间, 只有上交所L1可能会通过拆解SendingTime得到) */

    int32               instrId;                /**< 证券代码 (转换为整数类型的证券代码) */
    int16               bodyLength;             /**< 实际数据长度 */
    uint8               mdStreamType;           /**< 行情数据类型 @see eMdsMdStreamTypeT */
    uint8               __channelNo;            /**< 内部频道号 (供内部使用, 取值范围{1,2,4,8}) */
    uint32              __dataVersion;          /**< 行情数据的更新版本号 */
    uint32              __origTickSeq;          /**< 对应的原始行情的序列号 (供内部使用) */
    uint32              __directSourceId;       /**< 内部数据来源标识 (仅内部使用) */

#if defined (_MDS_ENABLE_LATENCY_STATS) || defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
    /** 消息原始接收时间 (从网络接收到数据的最初时间) */
    STimespec32T        __origNetTime;
#endif
#if defined (_MDS_ENABLE_LATENCY_STATS)
    /** 消息实际接收时间 (开始解码等处理之前的时间) */
    STimespec32T        __recvTime;
    /** 消息采集处理完成时间 */
    STimespec32T        __collectedTime;
    /** 消息加工处理完成时间 */
    STimespec32T        __processedTime;
    /** 消息推送时间 (写入推送缓存以后, 实际网络发送之前) */
    STimespec32T        __pushingTime;
#endif

} MdsMktDataSnapshotHeadT;


/* 结构体初始化值的尾部填充字段定义 */
#if defined (_MDS_ENABLE_LATENCY_STATS)
# define    __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER                 \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#elif defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
# define    __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER                 \
            , {0, 0}
#else
# define    __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER
#endif


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD                              \
        NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD3(0, 0, 0)

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD2(EXCH_ID, MD_SOURCE)         \
        NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD3(EXCH_ID, 0, (MD_SOURCE))

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD3(EXCH_ID, SECURITY_TYPE,     \
                MD_SOURCE)                                              \
        (EXCH_ID), (SECURITY_TYPE), 0, (MD_SOURCE), \
        0, 0, \
        0, 0, 0, 0, 0, 0, 0 \
        __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER
/* -------------------------           */


/**
 * Level1/Level2 指数快照行情定义
 */
typedef struct _MdsIndexSnapshotBody {
    /** 证券代码 C6 / C8 (如: '000001' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];
    /**
     * 产品实时阶段及标志 C8 (对于指数行情该字段为预留字段)
     * @see MdsStockSnapshotBodyT.TradingPhaseCode
     */
    char                TradingPhaseCode[MDS_MAX_TRADING_PHASE_CODE_LEN];
    char                __filler[6];            /**< 按64位对齐的填充域 */

    uint64              NumTrades;              /**< 成交笔数 (仅适用于深交所, 上交所指数行情中没有成交笔数信息) */
    uint64              TotalVolumeTraded;      /**< 成交总量 (@note 上交所指数的成交量单位是手, 深交所指数的成交量单位是股) */
    int64               TotalValueTraded;       /**< 成交总金额 (金额单位精确到元后四位, 即: 1元=10000) */

    int64               PrevCloseIdx;           /**< 昨日收盘指数 (价格单位精确到元后四位, 即: 1元=10000) */
    int64               OpenIdx;                /**< 今开盘指数 (价格单位精确到元后四位, 即: 1元=10000) */
    int64               HighIdx;                /**< 最高指数 */
    int64               LowIdx;                 /**< 最低指数 */
    int64               LastIdx;                /**< 最新指数 */
    int64               CloseIdx;               /**< 今收盘指数 */

    int32               StockNum;               /**< 统计量指标样本个数 (用于深交所成交量统计指标) */
    int32               __filler1;              /**< 按64位对齐的填充域 */
} MdsIndexSnapshotBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_INDEX_SNAPSHOT_BODY                                 \
        {0}, {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0
/* -------------------------           */


/**
 * Level1 股票快照行情定义
 * 股票(A、B股)、债券、基金、期权
 *
 * 关于集合竞价期间的虚拟集合竞价行情 (上交所L1、深交所L1):
 * - 集合竞价期间的虚拟成交价通过买卖盘档位揭示, 其中买一和卖一都揭示虚拟成交价格和成交数量,
 *   买二或卖二揭示虚拟成交价位上的买剩余量或卖剩余量
 */
typedef struct _MdsStockSnapshotBody {
    /** 证券代码 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 产品实时阶段及标志 C8 / C4
     *
     * 上交所股票 (C8):
     *  -# 第 0 位:
     *      - ‘S’表示启动 (开市前) 时段, ‘C’表示开盘集合竞价时段, ‘T’表示连续交易时段,
     *      - ‘E’表示闭市时段, ‘P’表示产品停牌,
     *      - ‘M’表示可恢复交易的熔断时段 (盘中集合竞价), ‘N’表示不可恢复交易的熔断时段 (暂停交易至闭市),
     *      - ‘U’表示收盘集合竞价时段。
     *  -# 第 1 位:
     *      - ‘0’表示此产品不可正常交易,
     *      - ‘1’表示此产品可正常交易,
     *      - 无意义填空格。
     *      - 在产品进入开盘集合竞价、连续交易、收盘集合竞价、熔断(盘中集合竞价)状态时值为‘1’,
     *        在产品进入停牌、熔断(暂停交易至闭市)状态时值为‘0’, 且闭市后保持该产品闭市前的是否可正常交易状态。
     *  -# 第 2 位:
     *      - ‘0’表示未上市, ‘1’表示已上市。
     *  -# 第 3 位:
     *      - ‘0’表示此产品在当前时段不接受订单申报,
     *      - ‘1’表示此产品在当前时段可接受订单申报。
     *      - 仅在交易时段有效，在非交易时段无效。无意义填空格。
     *
     * 上交所期权 (C4):
     *  -# 第 0 位:
     *      - ‘S’表示启动(开市前)时段, ‘C’表示集合竞价时段, ‘T’表示连续交易时段,
     *      - ‘B’表示休市时段, ‘E’表示闭市时段, ‘V’表示波动性中断, ‘P’表示临时停牌, ‘U’收盘集合竞价。
     *      - ‘M’表示可恢复交易的熔断 (盘中集合竞价), ‘N’表示不可恢复交易的熔断 (暂停交易至闭市)
     *  -# 第 1 位:
     *      - ‘0’表示未连续停牌, ‘1’表示连续停牌。(预留, 暂填空格)
     *  -# 第 2 位:
     *      - ‘0’表示不限制开仓, ‘1’表示限制备兑开仓, ‘2’表示卖出开仓, ‘3’表示限制卖出开仓、备兑开仓,
     *      - ‘4’表示限制买入开仓, ‘5’表示限制买入开仓、备兑开仓, ‘6’表示限制买入开仓、卖出开仓,
     *      - ‘7’表示限制买入开仓、卖出开仓、备兑开仓
     *  -# 第 3 位:
     *      - ‘0’表示此产品在当前时段不接受进行新订单申报,
     *      - ‘1’表示此产品在当前时段可接受进行新订单申报。
     *      - 仅在交易时段有效，在非交易时段无效。
     *
     * 深交所 (C8):
     *  -# 第 0 位:
     *      - S=启动(开市前) O=开盘集合竞价 T=连续竞价
     *      - B=休市 C=收盘集合竞价 E=已闭市 H=临时停牌
     *      - A=盘后交易 V=波动性中断
     *  -# 第 1 位:
     *      - 0=正常状态
     *      - 1=全天停牌
     */
    char                TradingPhaseCode[MDS_MAX_TRADING_PHASE_CODE_LEN];
    char                __filler[6];            /**< 按64位对齐的填充域 */

    uint64              NumTrades;              /**< 成交笔数 */
    uint64              TotalVolumeTraded;      /**< 成交总量 (上交所债券的数量单位为手) */
    int64               TotalValueTraded;       /**< 成交总金额 (金额单位精确到元后四位, 即: 1元=10000) */

    int32               PrevClosePx;            /**< 昨日收盘价 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               OpenPx;                 /**< 今开盘价 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               HighPx;                 /**< 最高价 */
    int32               LowPx;                  /**< 最低价 */
    int32               TradePx;                /**< 成交价 (最新价) */
    int32               ClosePx;                /**< 今收盘价/期权收盘价 (仅适用于上交所, 深交所行情没有单独的收盘价) */

    int32               IOPV;                   /**< 基金份额参考净值/ETF申赎的单位参考净值 (适用于基金) */
    int32               NAV;                    /**< 基金 T-1 日净值 (适用于基金, 上交所Level-2实时行情里面没有该字段) */
    uint64              TotalLongPosition;      /**< 合约总持仓量 (适用于期权) */

    /** 五档买盘价位信息 */
    MdsPriceLevelEntryT BidLevels[5];

    /** 五档卖盘价位信息 */
    MdsPriceLevelEntryT OfferLevels[5];

} MdsStockSnapshotBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_STOCK_SNAPSHOT_BODY                                 \
        {0}, {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }
/* -------------------------           */


/**
 * Level1 证券行情全幅消息的完整消息体定义
 */
typedef union _MdsL1SnapshotBody {
    /** 股票、债券、基金行情数据 */
    MdsStockSnapshotBodyT
                        stock;

    /** 期权行情数据 */
    MdsStockSnapshotBodyT
                        option;

    /** 指数行情数据 */
    MdsIndexSnapshotBodyT
                        index;
} MdsL1SnapshotBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L1_SNAPSHOT_BODY                                    \
        {NULLOBJ_MDS_STOCK_SNAPSHOT_BODY}
/* -------------------------           */


/**
 * 完整的 Level1 证券行情全幅消息定义
 */
typedef struct _MdsL1Snapshot {
    /** 行情数据的消息头 */
    MdsMktDataSnapshotHeadT
                        head;

    union {
        /** 股票、债券、基金行情数据 */
        MdsStockSnapshotBodyT
                        stock;

        /** 期权行情数据 */
        MdsStockSnapshotBodyT
                        option;

        /** 指数行情数据 */
        MdsIndexSnapshotBodyT
                        index;
    };
} MdsL1SnapshotT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L1_SNAPSHOT                                         \
        {NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD}, \
        {{NULLOBJ_MDS_STOCK_SNAPSHOT_BODY}}
/* -------------------------           */


/* ===================================================================
 * Level2 快照行情消息定义
 * =================================================================== */

/**
 * Level2 快照行情定义
 * 股票(A、B股)、债券、基金
 *
 * 关于集合竞价期间的虚拟集合竞价行情 (上交所L2、深交所L2):
 * - 集合竞价期间的虚拟成交价通过买卖盘档位揭示, 其中买一和卖一都揭示虚拟成交价格和成交数量,
 *   买二或卖二揭示虚拟成交价位上的买剩余量或卖剩余量
 */
typedef struct _MdsL2StockSnapshotBody {
    /** 证券代码 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 产品实时阶段及标志 C8 / C4
     *
     * 上交所股票 (C8):
     *  -# 第 0 位:
     *      - ‘S’表示启动 (开市前) 时段, ‘C’表示开盘集合竞价时段, ‘T’表示连续交易时段,
     *      - ‘E’表示闭市时段, ‘P’表示产品停牌,
     *      - ‘M’表示可恢复交易的熔断时段 (盘中集合竞价), ‘N’表示不可恢复交易的熔断时段 (暂停交易至闭市),
     *      - ‘U’表示收盘集合竞价时段。
     *  -# 第 1 位:
     *      - ‘0’表示此产品不可正常交易,
     *      - ‘1’表示此产品可正常交易,
     *      - 无意义填空格。
     *      - 在产品进入开盘集合竞价、连续交易、收盘集合竞价、熔断(盘中集合竞价)状态时值为‘1’,
     *        在产品进入停牌、熔断(暂停交易至闭市)状态时值为‘0’, 且闭市后保持该产品闭市前的是否可正常交易状态。
     *  -# 第 2 位:
     *      - ‘0’表示未上市, ‘1’表示已上市。
     *  -# 第 3 位:
     *      - ‘0’表示此产品在当前时段不接受订单申报,
     *      - ‘1’表示此产品在当前时段可接受订单申报。
     *      - 仅在交易时段有效，在非交易时段无效。无意义填空格。
     *
     * 上交所期权 (C4):
     *  -# 第 0 位:
     *      - ‘S’表示启动(开市前)时段, ‘C’表示集合竞价时段, ‘T’表示连续交易时段,
     *      - ‘B’表示休市时段, ‘E’表示闭市时段, ‘V’表示波动性中断, ‘P’表示临时停牌, ‘U’收盘集合竞价。
     *      - ‘M’表示可恢复交易的熔断 (盘中集合竞价), ‘N’表示不可恢复交易的熔断 (暂停交易至闭市)
     *  -# 第 1 位:
     *      - ‘0’表示未连续停牌, ‘1’表示连续停牌。(预留, 暂填空格)
     *  -# 第 2 位:
     *      - ‘0’表示不限制开仓, ‘1’表示限制备兑开仓, ‘2’表示卖出开仓, ‘3’表示限制卖出开仓、备兑开仓,
     *      - ‘4’表示限制买入开仓, ‘5’表示限制买入开仓、备兑开仓, ‘6’表示限制买入开仓、卖出开仓,
     *      - ‘7’表示限制买入开仓、卖出开仓、备兑开仓
     *  -# 第 3 位:
     *      - ‘0’表示此产品在当前时段不接受进行新订单申报,
     *      - ‘1’表示此产品在当前时段可接受进行新订单申报。
     *      - 仅在交易时段有效，在非交易时段无效。
     *
     * 深交所 (C8):
     *  -# 第 0 位:
     *      - S=启动(开市前) O=开盘集合竞价 T=连续竞价
     *      - B=休市 C=收盘集合竞价 E=已闭市 H=临时停牌
     *      - A=盘后交易 V=波动性中断
     *  -# 第 1 位:
     *      - 0=正常状态
     *      - 1=全天停牌
     */
    char                TradingPhaseCode[MDS_MAX_TRADING_PHASE_CODE_LEN];
    char                __filler[6];            /**< 按64位对齐的填充域 */

    uint64              NumTrades;              /**< 成交笔数 */
    uint64              TotalVolumeTraded;      /**< 成交总量 (上交所债券的数量单位为手) */
    int64               TotalValueTraded;       /**< 成交总金额 (金额单位精确到元后四位, 即: 1元=10000) */

    int32               PrevClosePx;            /**< 昨日收盘价 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               OpenPx;                 /**< 今开盘价 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               HighPx;                 /**< 最高价 */
    int32               LowPx;                  /**< 最低价 */
    int32               TradePx;                /**< 成交价 */
    int32               ClosePx;                /**< 今收盘价/期权收盘价 (仅适用于上交所, 深交所行情没有单独的收盘价) */

    int32               IOPV;                   /**< 基金份额参考净值/ETF申赎的单位参考净值 (适用于基金) */
    int32               NAV;                    /**< 基金 T-1 日净值 (适用于基金) */
    uint64              TotalLongPosition;      /**< 合约总持仓量 (适用于期权) */

    int64               TotalBidQty;            /**< 委托买入总量 */
    int64               TotalOfferQty;          /**< 委托卖出总量 */
    int32               WeightedAvgBidPx;       /**< 加权平均委买价格 */
    int32               WeightedAvgOfferPx;     /**< 加权平均委卖价格 */
    int32               BidPriceLevel;          /**< 买方委托价位数 (实际的委托价位总数, 仅适用于上交所) */
    int32               OfferPriceLevel;        /**< 卖方委托价位数 (实际的委托价位总数, 仅适用于上交所) */

    /** 十档买盘价位信息 */
    MdsPriceLevelEntryT BidLevels[10];

    /** 十档卖盘价位信息 */
    MdsPriceLevelEntryT OfferLevels[10];

} MdsL2StockSnapshotBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_STOCK_SNAPSHOT_BODY                              \
        {0}, {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }
/* -------------------------           */


/**
 * Level2 快照行情的增量更新消息定义 (增量更新消息仅适用于上交所L2)
 * 股票(A、B股)、债券、基金
 *
 * 关于增量更新消息补充说明如下:
 * -# 增量更新只有上交所Level2快照有, 深交所行情里面没有
 *    - 上交所的L2快照的更新频率为: 每3秒发送一次增量更新消息 (如果行情有变化的话),
 *      每60秒发送一次全量快照 (无论行情有无变化)。
 * -# 增量和全量快照的推送时点是一样的, 增量并不会比全量更快, 只是信息角度不一样
 *    - 在对下游系统进行推送时, 增量快照和完整快照在推送时间上是没有区别的;
 *    - MDS会先对交易所发下来的增量更新消息进行整合, 然后根据订阅条件向下游推送完整快照或增量
 *      更新消息。
 * -# 没有特别需求的话, 不需要订阅增量更新消息, 增量消息处理起来比较麻烦
 *
 * @note 上交所行情存在更新时间相同但数据不同的Level-2快照。(频率不高, 但会存在这样的数据)
 */
typedef struct _MdsL2StockSnapshotIncremental {
    uint64              NumTrades;              /**< 成交笔数 */
    uint64              TotalVolumeTraded;      /**< 成交总量 */
    int64               TotalValueTraded;       /**< 成交总金额 (金额单位精确到元后四位, 即: 1元=10000) */

    int32               OpenPx;                 /**< 今开盘价 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               HighPx;                 /**< 最高价 */
    int32               LowPx;                  /**< 最低价 */
    int32               TradePx;                /**< 成交价 */
    int32               ClosePx;                /**< 今收盘价/期权收盘价 (仅适用于上交所, 深交所行情没有单独的收盘价) */
    int32               IOPV;                   /**< 基金份额参考净值/ETF申赎的单位参考净值 (适用于基金) */

    int64               TotalBidQty;            /**< 委托买入总量 (上交所债券的数量单位为手) */
    int64               TotalOfferQty;          /**< 委托卖出总量 (上交所债券的数量单位为手) */
    int32               WeightedAvgBidPx;       /**< 加权平均委买价格 */
    int32               WeightedAvgOfferPx;     /**< 加权平均委卖价格 */
    int32               BidPriceLevel;          /**< 买方委托价位数 (实际的委托价位总数, 仅适用于上交所) */
    int32               OfferPriceLevel;        /**< 卖方委托价位数 (实际的委托价位总数, 仅适用于上交所) */

    /** 最优申买价 */
    int32               BestBidPrice;
    /** 增量更新消息中是否已经包含了最优申买价位 */
    uint8               HasContainedBestBidLevel;
    /** 买盘价位数量 (不包括已删除且大于最优申买价的价位) */
    uint8               NoBidLevel;
    /** 买盘价位列表中是否有从队列尾部删除的价位 */
    uint8               __hasDeletedAtBidTail;
    /** 按64位对齐的填充域 */
    uint8               __filler1;

    /** 最优申卖价 */
    int32               BestOfferPrice;
    /** 增量更新消息中是否已经包含了最优申买价位 */
    uint8               HasContainedBestOfferLevel;
    /** 卖盘价位数量 (不包括已删除且小于最优申卖价的价位) */
    uint8               NoOfferLevel;
    /** 卖盘价位列表中是否有从队列尾部删除的价位 */
    uint8               __hasDeletedAtOfferTail;
    /** 按64位对齐的填充域 */
    uint8               __filler2;

    /**
     * (发生变更的价位列表中) 各个价位的运算操作
     * - 1 = Add
     * - 2 = Update
     * - 3 = Delete
     * @see eMdsL2PriceLevelOperatorT
     */
    uint8               PriceLevelOperator[MDS_MAX_L2_PRICE_LEVEL_INCREMENTS];

    /** 发生变更的价位列表 (该字段为变长数组, 实际元素数量为: NoBidLevel + NoOfferLevel) */
    MdsPriceLevelEntryT PriceLevels[MDS_MAX_L2_PRICE_LEVEL_INCREMENTS];

} MdsL2StockSnapshotIncrementalT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_STOCK_SNAPSHOT_INCREMENTAL_BODY                  \
        0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        {0}, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }
/* -------------------------           */


/**
 * Level2 委托队列信息 (买一／卖一前五十笔委托明细)
 */
typedef struct _MdsL2BestOrdersSnapshotBody {
    /** 证券代码 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];
    uint8               __filler[5];            /**< 按64位对齐的填充域 */
    uint8               NoBidOrders;            /**< 买一价位的揭示委托笔数 */
    uint8               NoOfferOrders;          /**< 卖一价位的揭示委托笔数 */

    uint64              TotalVolumeTraded;      /**< 成交总量 (来自快照行情的冗余字段) */
    int32               BestBidPrice;           /**< 最优申买价 */
    int32               BestOfferPrice;         /**< 最优申卖价 */

    /** 买一价位的委托明细(前50笔) */
    int32               BidOrderQty[MDS_MAX_L2_DISCLOSE_ORDERS_CNT];

    /** 卖一价位的委托明细(前50笔) */
    int32               OfferOrderQty[MDS_MAX_L2_DISCLOSE_ORDERS_CNT];

} MdsL2BestOrdersSnapshotBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_BEST_ORDERS_SNAPSHOT_BODY                        \
        {0}, {0}, \
        0, 0, \
        0, 0, 0, \
        {0}, \
        {0}
/* -------------------------           */


/**
 * Level2 委托队列的增量更新信息 (买一／卖一前五十笔委托明细, 增量更新消息仅适用于上交所L2)
 */
typedef struct _MdsL2BestOrdersSnapshotIncremental {
    /** 成交总量 (来自快照行情的冗余字段) */
    uint64              TotalVolumeTraded;

    /** 最优申买价 */
    int32               BestBidPrice;
    /** 增量更新消息中是否已经包含了最优申买价位 */
    uint8               HasContainedBestBidLevel;
    /** 当前最优申买价下被连续删除掉的订单笔数 */
    uint8               ContinualDeletedBidOrders;
    /** 买盘需要更新的笔数 (不包括被连续删除掉的订单) */
    uint8               NoBidOrders;
    /** 按64位对齐的填充域 */
    uint8               __filler1;

    /** 最优申卖价 */
    int32               BestOfferPrice;
    /** 增量更新消息中是否已经包含了最优申买价位 */
    uint8               HasContainedBestOfferLevel;
    /** 当前最优申卖价下被连续删除掉的订单笔数 */
    uint8               ContinualDeletedOfferOrders;
    /** 卖盘需要更新的笔数 (不包括被连续删除掉的订单) */
    uint8               NoOfferOrders;
    /** 按64位对齐的填充域 */
    uint8               __filler2;

    /**
     * (发生变更的委托明细中) 待更新或删除的订单位置 (即需要删除和更新的上一次订单的位置)
     * - 订单位置从 0 开始
     * - 小于0, 表示删除该位置的订单
     * - 大于等于0, 表示更新该位置的订单
     * - CHAR_MAX, 表示新增
     */
    int8                OperatorEntryID[MDS_MAX_L2_DISCLOSE_ORDERS_INCREMENTS];

    /** 发生变更的委托明细 (该字段为变长数组, 实际元素数量为: NoBidOrders + NoOfferOrders) */
    int32               OrderQty[MDS_MAX_L2_DISCLOSE_ORDERS_INCREMENTS];

} MdsL2BestOrdersSnapshotIncrementalT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_BEST_ORDERS_SNAPSHOT_INCREMENTAL                 \
        0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        {0}, \
        {0}
/* -------------------------           */


/**
 * Level2 市场总览消息定义
 */
typedef struct _MdsL2MarketOverview {
    int32               OrigDate;               /**< 市场日期 (YYYYMMDD) */
    int32               OrigTime;               /**< 市场时间 (HHMMSSss0, 实际精度为百分之一秒(HHMMSSss)) */

    int32               __exchSendingTime;      /**< 交易所发送时间 (HHMMSS000, 实际精度为秒(HHMMSS)) */
    int32               __mdsRecvTime;          /**< MDS接收到时间 (HHMMSSsss) */
} MdsL2MarketOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_MARKET_OVERVIEW                                  \
        0, 0, \
        0, 0
/* -------------------------           */


/**
 * Level2 快照行情的完整消息体定义
 */
typedef union _MdsL2SnapshotBody {
    /** Level2 快照行情(股票、债券、基金、期权) */
    MdsL2StockSnapshotBodyT
                        l2Stock;

    /** Level2 快照行情的增量更新消息 */
    MdsL2StockSnapshotIncrementalT
                        l2StockIncremental;

    /** Level2 委托队列(买一／卖一前五十笔委托明细) */
    MdsL2BestOrdersSnapshotBodyT
                        l2BestOrders;

    /** Level2 委托队列(买一／卖一前五十笔委托明细)的增量更新消息 */
    MdsL2BestOrdersSnapshotIncrementalT
                        l2BestOrdersIncremental;

    /** 指数行情数据 */
    MdsIndexSnapshotBodyT
                        index;

    /** Level2 市场总览 (仅适用于上交所) */
    MdsL2MarketOverviewT
                        l2MarketOverview;
} MdsL2SnapshotBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_SNAPSHOT_BODY                                    \
        {NULLOBJ_MDS_L2_STOCK_SNAPSHOT_BODY}
/* -------------------------           */


/**
 * (对外发布的) 完整的 Level1/Level2 快照行情定义
 */
typedef struct _MdsMktDataSnapshot {
    /** 行情数据的消息头 */
    MdsMktDataSnapshotHeadT
                        head;

    union {
        /** Level2 快照行情(股票、债券、基金) */
        MdsL2StockSnapshotBodyT
                        l2Stock;

        /** Level2 快照行情的增量更新消息 */
        MdsL2StockSnapshotIncrementalT
                        l2StockIncremental;

        /** Level2 委托队列(买一／卖一前五十笔委托明细) */
        MdsL2BestOrdersSnapshotBodyT
                        l2BestOrders;

        /** Level2 委托队列(买一／卖一前五十笔委托明细)的增量更新消息 */
        MdsL2BestOrdersSnapshotIncrementalT
                        l2BestOrdersIncremental;

        /** Level1 股票、债券、基金行情数据 */
        MdsStockSnapshotBodyT
                        stock;

        /** Level1/Level2 期权行情数据 */
        MdsStockSnapshotBodyT
                        option;

        /** Level1/Level2 指数行情数据 */
        MdsIndexSnapshotBodyT
                        index;

        /** Level2 市场总览 (仅适用于上交所) */
        MdsL2MarketOverviewT
                        l2MarketOverview;
    };
} MdsMktDataSnapshotT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT                                   \
        {NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD}, \
        {{NULLOBJ_MDS_L2_STOCK_SNAPSHOT_BODY}}


/* 结构体大小定义 */
#define DATASIZE_MDS_L2_STOCK_SNAPSHOT                                  \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsL2StockSnapshotBodyT))

#define DATASIZE_MDS_L2_BEST_ORDERS_SNAPSHOT                            \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsL2BestOrdersSnapshotBodyT))

#define DATASIZE_MDS_STOCK_SNAPSHOT                                     \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsStockSnapshotBodyT))

#define DATASIZE_MDS_OPTION_SNAPSHOT                                    \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsStockSnapshotBodyT))

#define DATASIZE_MDS_INDEX_SNAPSHOT                                     \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsIndexSnapshotBodyT))

#define DATASIZE_MDS_L2_MARKET_OVERVIEW                                 \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsL2MarketOverviewT))
/* -------------------------           */


/* ===================================================================
 * Level2 逐笔成交/逐笔委托行情消息定义
 * =================================================================== */

/**
 * Level2 逐笔成交行情定义
 */
typedef struct _MdsL2Trade {
    uint8               exchId;                 /**< 交易所代码(沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重复的行情 (内部使用, 小于0表示回补的逐笔重建数据) */
    uint8               __origMdSource;         /**< 原始行情数据来源 @see eMdsMsgSourceT */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 非官方数据) */
    int32               TransactTime;           /**< 成交时间 (HHMMSSsss) */

    int32               instrId;                /**< 证券代码 (转换为整数类型的证券代码) */
    int32               ChannelNo;              /**< 频道代码 [0..9999] */
    /**
     * 深交所消息记录号/上交所成交序号 (从1开始, 按频道连续)
     * - 深交所为逐笔成交+逐笔委托统一编号
     * - 上交所为逐笔成交独立编号 (TradeIndex)
     */
    int32               ApplSeqNum;

    /** 证券代码 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];
    /**
     * 成交类别 (仅适用于深交所)
     * - 深交所: '4'=撤销, 'F'=成交
     * - 上交所: 将固定为 'F' (成交)
     * - @see eMdsL2TradeExecTypeT
     */
    char                ExecType;
    /**
     * 内外盘标志 (仅适用于上交所)
     * - 上交所: 'B'=外盘(主动买), 'S'=内盘(主动卖), 'N'=未知
     * - 深交所: 将固定为 'N' (未知)
     * - @see eMdsL2TradeBSFlagT
     */
    char                TradeBSFlag;
    /** 内部频道号 (供内部使用, 取值范围{1,2,4,8}) */
    uint8               __channelNo;

    /**
     * 业务序列号 (仅适用于上交所)
     * - 仅适用于上交所, 逐笔成交+逐笔委托统一编号, 从1开始, 按频道连续
     * - 对于深交所, 该字段将固定为 0
     */
    uint32              SseBizIndex;
    /** 为保持协议兼容而定义的填充域 */
    uint64              __filler;

    /** 成交价格 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               TradePrice;
    /** 成交数量 (仅上交所债券的数量单位为手, 其它均为股或张) */
    int32               TradeQty;
    /** 成交金额 (金额单位精确到元后四位, 即: 1元=10000) */
    int64               TradeMoney;

    /**
     * 买方订单号 (从 1 开始计数, 0 表示无对应委托)
     * - 对于深交所, 该字段对应于买方逐笔委托的 ApplSeqNum 字段
     * - 对于上交所, 该字段对应于买方逐笔委托的 SseOrderNo 字段
     */
    int64               BidApplSeqNum;
    /**
     * 卖方订单号 (从 1 开始计数, 0 表示无对应委托)
     * - 对于深交所, 该字段对应于卖方逐笔委托的 ApplSeqNum 字段
     * - 对于上交所, 该字段对应于卖方逐笔委托的 SseOrderNo 字段
     */
    int64               OfferApplSeqNum;

#if defined (_MDS_ENABLE_LATENCY_STATS) || defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
    /** 消息原始接收时间 (从网络接收到数据的最初时间) */
    STimespec32T        __origNetTime;
#endif
#if defined (_MDS_ENABLE_LATENCY_STATS)
    /** 消息实际接收时间 (开始解码等处理之前的时间) */
    STimespec32T        __recvTime;
    /** 消息采集处理完成时间 */
    STimespec32T        __collectedTime;
    /** 消息加工处理完成时间 */
    STimespec32T        __processedTime;
    /** 消息推送时间 (写入推送缓存以后, 实际网络发送之前) */
    STimespec32T        __pushingTime;
#endif

} MdsL2TradeT;


/* 结构体初始化值的尾部填充字段定义 */
#if defined (_MDS_ENABLE_LATENCY_STATS)
# define    __NULLOBJ_MDS_L2_TRADE_TAILER                               \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#elif defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
# define    __NULLOBJ_MDS_L2_TRADE_TAILER                               \
            , {0, 0}
#else
# define    __NULLOBJ_MDS_L2_TRADE_TAILER
#endif


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_TRADE                                            \
        NULLOBJ_MDS_L2_TRADE2(0, 0, 0, 0)


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_TRADE2(exchId, mdProductType, isRepeated,        \
                mdSource)                                               \
        (exchId), (mdProductType), (isRepeated), (mdSource), \
        0, 0, \
        0, 0, 0, \
        {0}, 0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        0, 0 \
        __NULLOBJ_MDS_L2_TRADE_TAILER
/* -------------------------           */


/**
 * Level2 逐笔委托行情定义
 */
typedef struct _MdsL2Order {
    uint8               exchId;                 /**< 交易所代码(沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重复的行情 (内部使用, 小于0表示回补的逐笔重建数据) */
    uint8               __origMdSource;         /**< 原始行情数据来源 @see eMdsMsgSourceT */

    int32               tradeDate;              /**< 交易日期 YYYYMMDD (自然日) */
    int32               TransactTime;           /**< 委托时间 HHMMSSsss */

    int32               instrId;                /**< 证券代码 (转换为整数类型的证券代码) */
    int32               ChannelNo;              /**< 频道代码 [0..9999] */
    /**
     * 深交所消息记录号/上交所委托序号 (从1开始, 按频道连续)
     * - 深交所为逐笔成交+逐笔委托统一编号
     * - 上交所为逐笔委托独立编号 (OrderIndex)
     */
    int32               ApplSeqNum;

    /** 证券代码 C6 / C8 (如: '000001' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];
    /**
     * 买卖方向
     * - 深交所: '1'=买, '2'=卖, 'G'=借入, 'F'=出借
     * - 上交所: '1'=买, '2'=卖
     */
    char                Side;
    /**
     * 订单类型
     * - 深交所: '1'=市价, '2'=限价, 'U'=本方最优
     * - 上交所: 'A'=委托订单-增加(新订单), 'D'=委托订单-删除(撤单)
     */
    char                OrderType;
    /** 内部频道号 (供内部使用, 取值范围{1,2,4,8}) */
    uint8               __channelNo;

    /**
     * 业务序列号 (仅适用于上交所)
     * - 仅适用于上交所, 逐笔成交+逐笔委托统一编号, 从1开始, 按频道连续
     * - 对于深交所, 该字段将固定为 0
     */
    uint32              SseBizIndex;
    /**
     * 原始订单号 (仅适用于上交所)
     * - 仅适用于上交所, 和逐笔成交中的买方/卖方订单号相对应
     * - 对于深交所, 该字段将固定为 0
     */
    int64               SseOrderNo;

    /** 委托价格 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               Price;
    /**
     * 委托数量
     * - @note 对于上交所, 该字段的含义为剩余委托量或撤单数量:
     *   - 对于上交所, 当 OrderType='A' 时, 该字段表示的是剩余委托量 (竞价撮合成交后的剩余委托数量)
     *   - 对于上交所, 当 OrderType='D' 时, 该字段表示的是撤单数量
     */
    int32               OrderQty;

#if defined (_MDS_ENABLE_LATENCY_STATS) || defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
    /** 消息原始接收时间 (从网络接收到数据的最初时间) */
    STimespec32T        __origNetTime;
#endif
#if defined (_MDS_ENABLE_LATENCY_STATS)
    /** 消息实际接收时间 (开始解码等处理之前的时间) */
    STimespec32T        __recvTime;
    /** 消息采集处理完成时间 */
    STimespec32T        __collectedTime;
    /** 消息加工处理完成时间 */
    STimespec32T        __processedTime;
    /** 消息推送时间 (写入推送缓存以后, 实际网络发送之前) */
    STimespec32T        __pushingTime;
#endif

} MdsL2OrderT;


/* 结构体初始化值的尾部填充字段定义 */
#if defined (_MDS_ENABLE_LATENCY_STATS)
# define    __NULLOBJ_MDS_L2_ORDER_TAILER                               \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#elif defined (_MDS_ENABLE_ORIG_NET_TIMESTAMP)
# define    __NULLOBJ_MDS_L2_ORDER_TAILER                               \
            , {0, 0}
#else
# define    __NULLOBJ_MDS_L2_ORDER_TAILER
#endif


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_ORDER                                            \
        NULLOBJ_MDS_L2_ORDER2(0, 0, 0, 0)


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_L2_ORDER2(exchId, mdProductType, isRepeated,        \
                mdSource)                                               \
        (exchId), (mdProductType), (isRepeated), (mdSource), \
        0, 0, \
        0, 0, 0, \
        {0}, 0, 0, 0, \
        0, 0, \
        0, 0 \
        __NULLOBJ_MDS_L2_ORDER_TAILER
/* -------------------------           */


/* ===================================================================
 * 汇总的行情数据定义
 * =================================================================== */

/**
 * 完整的行情数据消息体定义
 */
typedef union _MdsWholeMktMsgBody {
    /** 快照行情 (Level1 快照 / Level2 快照 / 指数行情 / 期权行情) */
    MdsMktDataSnapshotT mktDataSnapshot;

    /** Level2 逐笔成交行情 */
    MdsL2TradeT         trade;

    /** Level2 逐笔委托行情 */
    MdsL2OrderT         order;

    /** 市场状态消息 (仅适用于上交所) */
    MdsTradingSessionStatusMsgT
                        trdSessionStatus;

    /** 证券实时状态消息 (仅适用于深交所) */
    MdsSecurityStatusMsgT
                        securityStatus;
} MdsWholeMktMsgBodyT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_WHOLE_MKT_MSG_BODY                                  \
        {NULLOBJ_MDS_MKT_DATA_SNAPSHOT}
/* -------------------------           */


/* ===================================================================
 * 证券信息等静态数据定义
 * =================================================================== */

/**
 * 证券信息(股票/基金/债券)的静态数据结构体定义
 */
typedef struct _MdsStockStaticInfo {
    /** 证券代码 C6 / C8 (如: '600000' 等) */
    char                securityId[MDS_MAX_INSTR_CODE_LEN];
    uint8               exchId;                 /**< 交易所代码 (沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/期权/指数) @see eMdsMdProductTypeT */
    uint8               oesSecurityType;        /**< 证券类型 (股票/债券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 证券子类型 @see eOesSubSecurityTypeT */
    uint8               currType;               /**< 币种 @see eOesCurrTypeT */
    uint8               qualificationClass;     /**< 投资者适当性管理分类 @see eOesQualificationClassT */
    uint8               __filler1[5];           /**< 按64位对齐的填充域 */
    int32               instrId;                /**< 证券代码 (转换为整数类型的证券代码) */

    uint32              securityStatus;         /**< 证券状态 @see eOesSecurityStatusT */
    uint32              securityAttribute;      /**< 证券属性 @see eOesSecurityAttributeT */

    uint8               suspFlag;               /**< 连续停牌标识 (0 未停牌, 1 已停牌) */
    uint8               isDayTrading;           /**< 是否支持当日回转交易 (0 不支持, 1 支持) */
    uint8               isRegistration;         /**< 是否注册制 (0 核准制, 1 注册制) */
    uint8               isCrdCollateral;        /**< 是否为融资融券担保品 (0 不是担保品, 1 是担保品) */
    /** 是否为融资标的 (0 不是融资标的, 1 是融资标的) */
    uint8               isCrdMarginTradeUnderlying;
    /** 是否为融券标的 (0 不是融券标的, 1 是融券标的) */
    uint8               isCrdShortSellUnderlying;
    uint8               isNoProfit;             /**< 是否尚未盈利 (0 已盈利, 1 未盈利 (仅适用于科创板和创业板产品)) */
    uint8               isWeightedVotingRights; /**< 是否存在投票权差异 (0 无差异, 1 存在差异 (仅适用于科创板和创业板产品)) */
    uint8               isVie;                  /**< 是否具有协议控制框架 (0 没有, 1 有 (仅适用于创业板产品)) */
    uint8               __filler2[7];           /**< 按64位对齐的填充域 */

    union {
        int32           upperLimitPrice;        /**< 涨停价 (单位精确到元后四位, 即: 1元=10000) */
        int32           limitUpPrice;           /**< 涨停价 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    union {
        int32           lowerLimitPrice;        /**< 跌停价 (单位精确到元后四位, 即: 1元=10000) */
        int32           limitDownPrice;         /**< 跌停价 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    int32               priceTick;              /**< 价格档位 (价格单位精确到元后四位, 即: 1元=10000) */
    int32               prevClose;              /**< 前收盘价 (价格单位精确到元后四位, 即: 1元=10000) */

    union {
        int32           lmtBuyMaxQty;           /**< 单笔限价买委托数量上限 */
        int32           buyOrdMaxQty;           /**< 单笔限价买委托数量上限 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    union {
        int32           lmtBuyMinQty;           /**< 单笔限价买委托数量下限 */
        int32           buyOrdMinQty;           /**< 单笔限价买委托数量下限 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    union {
        int32           lmtBuyQtyUnit;          /**< 单笔限价买入单位 */
        int32           buyQtyUnit;             /**< 单笔限价买入单位 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    int32               mktBuyQtyUnit;          /**< 单笔市价买入单位 */
    int32               mktBuyMaxQty;           /**< 单笔市价买委托数量上限 */
    int32               mktBuyMinQty;           /**< 单笔市价买委托数量下限 */

    union {
        int32           lmtSellMaxQty;          /**< 单笔限价卖委托数量上限 */
        int32           sellOrdMaxQty;          /**< 单笔限价卖委托数量上限 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    union {
        int32           lmtSellMinQty;          /**< 单笔限价卖委托数量下限 */
        int32           sellOrdMinQty;          /**< 单笔限价卖委托数量下限 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    union {
        int32           lmtSellQtyUnit;         /**< 单笔限价卖出单位 */
        int32           sellQtyUnit;            /**< 单笔限价卖出单位 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };
    int32               mktSellQtyUnit;         /**< 单笔市价卖出单位 */
    int32               mktSellMaxQty;          /**< 单笔市价卖委托数量上限 */
    int32               mktSellMinQty;          /**< 单笔市价卖委托数量下限 */

    int64               bondInterest;           /**< 债券的每张应计利息 (单位精确到元后八位) */
    union {
        int64           parValue;               /**< 面值 (价格单位精确到元后四位, 即: 1元=10000) */
        int64           parPrice;               /**< 面值 @deprecated 已废弃, 为了兼容旧版本而保留 */
    };

    uint8               auctionLimitType;       /**< 连续交易时段的有效竞价范围限制类型 @see eOesAuctionLimitTypeT */
    uint8               auctionReferPriceType;  /**< 连续交易时段的有效竞价范围基准价类型 @see eOesAuctionReferPriceTypeT */
    uint8               __filler3[2];           /**< 按64位对齐的填充域 */
    int32               auctionUpDownRange;     /**< 连续交易时段的有效竞价范围涨跌幅度 (百分比或绝对价格, 取决于'有效竞价范围限制类型') */

    int32               listDate;               /**< 上市日期 */
    int32               maturityDate;           /**< 到期日期 (仅适用于债券等有发行期限的产品) */
    int64               outstandingShare;       /**< 总股本 (即: 总发行数量, 上交所无该字段, 未额外维护时取值为0) */
    int64               publicFloatShare;       /**< 流通股数量 */

    /** 基础证券代码 (标的产品代码) */
    char                underlyingSecurityId[MDS_MAX_INSTR_CODE_LEN];
    /** 按64位对齐的填充域 */
    uint8               __filler4[7];
    /** 证券名称 (UTF-8 编码) */
    char                securityName[MDS_MAX_SECURITY_NAME_LEN];
    /** 证券长名称 (UTF-8 编码) */
    char                securityLongName[MDS_MAX_SECURITY_LONG_NAME_LEN];
    /** 证券英文名称 */
    char                securityEnglishName[MDS_MAX_SECURITY_ENGLISH_NAME_LEN];
    /** ISIN代码 */
    char                securityIsinCode[MDS_MAX_SECURITY_ISIN_CODE_LEN];

    /** 预留的备用字段1 */
    char                __reserve1[24];
    /** 预留的备用字段2 */
    char                __reserve2[64];
} MdsStockStaticInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_STOCK_STATIC_INFO                                   \
        {0}, 0, 0, 0, 0, 0, 0, {0}, 0, \
        0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, \
        {0}, {0}, 0, 0, \
        {0}, {0}, {0}, 0, 0, 0, \
        {0}, {0}, {0}, 0, 0, 0, \
        0, {0}, \
        0, 0, {0}, 0, \
        0, 0, 0, 0, \
        {0}, {0}, {0}, {0}, {0}, {0}, \
        {0}, {0}
/* -------------------------           */


/**
 * 期权合约信息的静态数据结构体定义
 */
typedef struct _MdsOptionStaticInfo {
    /** 期权合约代码 C8 (如: '10001230' 等) */
    char                securityId[MDS_MAX_INSTR_CODE_LEN];
    uint8               exchId;                 /**< 交易所代码 (沪/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/期权/指数) @see eMdsMdProductTypeT */
    uint8               oesSecurityType;        /**< 证券类型 (股票/债券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 证券子类型 @see eOesSubSecurityTypeT */
    uint8               contractType;           /**< 合约类型 (认购/认沽) @see eOesOptContractTypeT */
    uint8               exerciseType;           /**< 行权方式 @see eOesOptExerciseTypeT */
    uint8               deliveryType;           /**< 交割方式 @see eOesOptDeliveryTypeT */
    uint8               __filler1[4];           /**< 按64位对齐的填充域 */
    int32               instrId;                /**< 证券代码 (转换为整数类型的期权合约代码) */

    int32               contractUnit;           /**< 合约单位 (经过除权除息调整后的单位) */
    int32               exercisePrice;          /**< 期权行权价 (经过除权除息调整后的价格, 单位精确到元后四位, 即: 1元=10000) */
    int32               deliveryDate;           /**< 交割日期 (格式为YYYYMMDD) */
    int32               deliveryMonth;          /**< 交割月份 (格式为YYYYMM) */

    int32               listDate;               /**< 上市日期 (格式为YYYYMMDD) */
    int32               lastTradeDay;           /**< 最后交易日 (格式为YYYYMMDD) */
    int32               exerciseBeginDate;      /**< 行权起始日期 (格式为YYYYMMDD) */
    int32               exerciseEndDate;        /**< 行权结束日期 (格式为YYYYMMDD) */

    int32               prevClosePrice;         /**< 合约前收盘价 (单位精确到元后四位, 即: 1元=10000) */
    int32               prevSettlPrice;         /**< 合约前结算价 (单位精确到元后四位, 即: 1元=10000) */
    int32               underlyingClosePrice;   /**< 标的证券前收盘价 (单位精确到元后四位, 即: 1元=10000) */

    int32               priceTick;              /**< 最小报价单位 (单位精确到元后四位, 即: 1元=10000) */
    int32               upperLimitPrice;        /**< 涨停价 (单位精确到元后四位, 即: 1元=10000) */
    int32               lowerLimitPrice;        /**< 跌停价 (单位精确到元后四位, 即: 1元=10000) */

    int32               buyQtyUnit;             /**< 买入单位 */
    int32               lmtBuyMaxQty;           /**< 限价买数量上限 (单笔申报的最大张数) */
    int32               lmtBuyMinQty;           /**< 限价买数量下限 (单笔申报的最小张数) */
    int32               mktBuyMaxQty;           /**< 市价买数量上限 (单笔申报的最大张数) */
    int32               mktBuyMinQty;           /**< 市价买数量下限 (单笔申报的最小张数) */

    int32               sellQtyUnit;            /**< 卖出单位 */
    int32               lmtSellMaxQty;          /**< 限价卖数量上限 (单笔申报的最大张数) */
    int32               lmtSellMinQty;          /**< 限价卖数量下限 (单笔申报的最小张数) */
    int32               mktSellMaxQty;          /**< 市价卖数量上限 (单笔申报的最大张数) */
    int32               mktSellMinQty;          /**< 市价卖数量下限 (单笔申报的最小张数) */

    int64               sellMargin;             /**< 单位保证金 (未上调的今卖开每张保证金, 单位精确到元后四位, 即: 1元=10000) */

    /** 期权合约交易所代码 */
    char                contractId[MDS_MAX_CONTRACT_EXCH_ID_LEN];
    /** 期权合约名称 (UTF-8 编码) */
    char                securityName[MDS_MAX_SECURITY_NAME_LEN];
    /** 标的证券代码 */
    char                underlyingSecurityId[MDS_MAX_INSTR_CODE_LEN];
    /** 按64位对齐的填充域 */
    uint8               __filler2[7];

    char                __reserve[32];          /**< 预留的备用字段 */
} MdsOptionStaticInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_OPTION_STATIC_INFO                                  \
        {0}, 0, 0, 0, 0, 0, 0, 0, {0}, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, \
        {0}, {0}, {0}, {0}, \
        {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_BASE_MODEL_H */
