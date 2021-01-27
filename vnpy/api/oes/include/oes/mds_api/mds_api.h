/*
 * Copyright 2016 the original author or authors.
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
 * @file    mds_api.h
 *
 * MDS (行情数据服务系统) 接口库
 *
 * @version 0.8.13      2016/10/24
 * @version 0.12        2016/11/30
 *          - 重构错误号定义, 使错误号从1000开始
 *          - 增加 MdsApi_GetErrorMsg 和 MdsApi_GetErrorMsg2 方法
 *          - 在登录报文中增加协议版本号信息, 并在登录时校验协议版本号的兼容性
 * @version 0.12.1      2016/12/21
 *          - 查询接口重命名
 *              - MdsApi_QryMktDataSnapshot -> MdsApi_QueryMktDataSnapshot
 *              - MdsApi_QrySecurityStatus -> MdsApi_QuerySecurityStatus
 *              - MdsApi_QryTrdSessionStatus -> MdsApi_QueryTrdSessionStatus
 *          - 删除 MdsApi_IsBusinessError 接口, 查询接口不再返回小于 -1000 的错误
 *          - 查询接口返回值变更:
 *              - 无数据返回 SPK_NEG(ENOENT)
 *              - 查询被服务器拒绝返回 SPK_NEG(EINVAL), 具体错误信息通过日志打印
 *          - 微调mds_api日志打印格式
 * @version 0.12.3      2017/1/8
 *          - 精简API依赖的头文件, 并最小化API发布包中的头文件数量
 *          - 重命名 protocol_parser/errors/mds_protocol_errors.h -> errors/mds_errors.h
 *          - 添加辅助实现实时行情订阅功能的接口
 *              - MdsApi_ResubscribeMarketData
 *              - MdsHelper_ClearSubscribeRequestEntries
 *              - MdsHelper_AddSubscribeRequestEntry
 * @version 0.12.6.3    2017/03/24
 *          - 增加mds_api.h中的头文件引用, api使用者不在需要显式引用sutil库的头文件
 * @version 0.12.8      2017/04/20
 *          - 重命名 MdsApi_SubscribeMarketData -> MdsApi_SyncSubscribeOnLogon
 *          - 重命名 MdsApi_ResubscribeMarketData -> MdsApi_SubscribeMarketData
 *          - 添加辅助的行情订阅接口
 *              - MdsApi_SubscribeByString
 *              - MdsApi_SubscribeByStringAndPrefixes
 *              - MdsHelper_SetSubscribeRequestMode
 *              - MdsHelper_SetSubscribeRequestTickType
 *              - MdsHelper_SetSubscribeRequestDataTypes
 * @version 0.15.3.3    2017/08/20
 *          - 新增接口 '重置线程级别的日志记录器名称 (MdsApi_ResetThreadLoggerName)',
 *            以支持为当前线程设置独立的日志文件
 * @version 0.15.4      2017/08/21
 *          - 新增接口 '获取API的发行版本号 (MdsApi_GetApiVersion)'
 * @version 0.15.4.1    2017/09/25
 *          - 服务器端删除了对JSON等通信协议等支持, 改为只支持二进制协议
 * @version 0.15.5      2017/11/11
 *          - 调整接口 MdsApi_InitAll, 以支持同时初始化多个组播通道
 * @version 0.15.5.1    2017/11/17
 *          - 增加 MdsApi_IsValidTcpChannel、MdsApi_IsValidUdpChannel 等接口, 用于判断通道是否已经连接且有效
 * @version 0.15.5.2    2018/01/29
 *          - 增加 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime 接口, 用于获取通道最近发送/接收消息的时间
 *          - 登录失败时, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 * @version 0.15.5.3    2018/01/24
 *          - 调整接口 MdsApi_InitAll, 增加一个函数参数 (pUdpTick2AddrKey), 以支持分别订阅逐笔成交和逐笔委托的行情组播
 * @version 0.15.5.9    2018/05/05
 *          - 增加可以处理压缩过的消息的 WaitOnMsg 接口:
 *              - MdsApi_WaitOnMsgCompressible
 *              - MdsApi_WaitOnTcpChannelGroupCompressible
 *              - 与不带 Compressible 后缀的接口相比, 带 Compressible 后缀的接口会自动检测和处理压缩过的消息,
 *                但也会因此带来微小的性能损失。如果对延迟不是极端敏感的话, 可以直接使用带 Compressible 后缀的接
 *                口, 以方便兼容不同的模式。
 * @version 0.15.5.12   2018/06/21
 *          - 增加 MdsApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
 * @version 0.15.5.16   2018/08/23
 *          - 重构 SubscribeByString 接口
 *              - 支持订阅所有产品的行情或不订阅任何产品的行情
 *              - 支持通过 .SH 或 .SZ 后缀为证券代码指定其所属的交易所
 *              - 添加 MdsHelper_SetTickTypeOnSubscribeByString 接口, 以设置SubscribeByString默认使用的数据模式 (TickType)
 *              - 增量订阅时, 允许不指定 dataType (小于0) 而继承之前订阅的数据类型
 * @version 0.15.6      2018/03/21
 *          - 增加设置当前线程登录用户名/登录密码的接口
 *              - MdsApi_SetThreadUsername
 *              - MdsApi_SetThreadPassword
 *          - 增加返回最近一次API调用失败的错误号的接口
 *              - MdsApi_GetLastError
 *              - MdsApi_SetLastError
 * @version 0.15.7.6    2018/11/03
 *          - 增加查询证券(股票/债券/基金)静态信息的接口
 *              - MdsApi_QueryStockStaticInfo
 * @version 0.15.7.6_RC2 2018/11/11
 *          - 添加批量查询行情快照接口
 *              - MdsApi_QuerySnapshotList
 *          - 增加 MdsApi_InitAllByCfgStruct 接口
 * @version 0.15.9_I9   2019/04/15
 *          - 增加修改客户端登录密码接口
 *              - MdsApi_SendChangePasswordReq
 *          - 增加设置/获取客户端自定义的本地IP/MAC地址的接口
 *              - MdsApi_SetCustomizedIp
 *              - MdsApi_GetCustomizedIp
 *              - MdsApi_SetCustomizedMac
 *              - MdsApi_GetCustomizedMac
 *          - 增加设置/获取客户端自定义的设备序列号的接口
 *              - MdsApi_SetCustomizedDriverId
 *              - MdsApi_GetCustomizedDriverId
 *          - 重新实现登录接口 (接口MdsApi_Logon)
 *              - 增加采集IP、MAC等信息, 增强安全性处理
 *          - 调整L2逐笔数据的行情组播频道
 *              - 划分为两个频道, 按照频道号混合推送逐笔成交和逐笔委托, 取代之前逐笔成交/逐笔委托分别推送的方式
 *              - API及配置文件保持兼容, 但频道内容发生了变化
 * @version 0.15.9.1    2019/06/27
 *          - 增加为SubscribeByString设置附加订阅参数的接口
 *              - MdsApi_SetThreadSubscribeTickType
 *              - MdsApi_SetThreadSubscribeTickRebuildFlag
 *              - MdsApi_SetThreadSubscribeTickExpireType
 *              - MdsApi_SetThreadSubscribeRequireInitMd
 *              - MdsApi_SetThreadSubscribeBeginTime
 *          - 增加可以禁止登录后自动订阅行情的接口
 *              - MdsApi_SetThreadAutoSubscribeOnLogon
 *          - 完善对行情订阅条件中起始时间 (beginTime) 和初始行情标志 (isRequireInitialMktData) 的支持
 *              - 允许在会话过程中任意时间指定 beginTime 和 isRequireInitialMktData 订阅参数
 *              - 频繁指定 beginTime 和 isRequireInitialMktData 订阅参数, 会对当前客户
 *                端的行情获取速度产生不利影响。应谨慎使用, 避免频繁订阅
 *          - 优化行情订阅接口, 取消基础订阅接口一次最大只能订阅4000只证券代码的限制
 *              - MdsApi_SubscribeMarketData
 * @version 0.15.9.2    2019/10/08
 *          - 调整行情组播频道的划分
 *              - API及配置文件保持兼容, 但频道内容发生了变化
 *              - 划分为两个独立的沪/深快照频道和两个独立的沪/深逐笔频道, 共4个组播频道
 *                  - 快照-频道1, 上海L1/L2快照
 *                  - 快照-频道2, 深圳L1/L2快照
 *                  - 逐笔-频道1, 上海逐笔成交
 *                  - 逐笔-频道2, 深圳逐笔成交/逐笔委托
 *          - 对外开放之前仅内部使用的配置文件解析接口
 *              - MdsApi_ParseConfigFromFile2, 解析客户端配置文件, 并可以指定是否允许配置项为空
 * @version 0.15.10.6   2020/05/14
 *          - 将会话信息中的发送时间(lastSendTime)和接收时间(lastRecvTime)升级为纳秒级时间戳 (STimevalT => STimespecT)
 * @version 0.15.11     2020/05/29
 *          - 增加辅助的通道组接口
 *              - MdsApi_GetChannelGroupLastRecvTime, 返回通道组最近接收消息时间
 *              - MdsApi_GetChannelGroupLastSendTime, 返回通道组最近发送消息时间
 *          - 增加辅助判断现货产品状态的接口
 *              - MdsApi_HasStockStatus
 * @version 0.15.11.3   2020/06/29
 *          - 增加新的批量查询证券(股票/债券/基金)静态信息列表接口, 以支持同时指定和查询多个证券代码
 *              - MdsApi_QueryStockStaticInfoList, 批量查询证券(股票/债券/基金)静态信息列表
 *              - MdsApi_QueryStockStaticInfoList2, 批量查询证券(股票/债券/基金)静态信息列表 (字符串指针数组形式的证券代码列表)
 *          - 增加用于校验API版本号是否匹配的辅助函数
 *              - __MdsApi_CheckApiVersion
 * @version 0.16        2019/11/20
 *          - 增加查询期权合约静态信息的接口
 *              - MdsApi_QueryOptionStaticInfo
 * @version 0.16.1.1    2020/06/29
 *          - 增加新的批量查询期权静态信息列表接口, 以支持同时指定和查询多个期权合约代码
 *              - MdsApi_QueryOptionStaticInfoList, 批量查询期权静态信息列表
 *              - MdsApi_QueryOptionStaticInfoList2, 批量查询期权静态信息列表 (字符串指针数组形式的证券代码列表)
 *
 * @since   2016/03/02
 */


#ifndef _MDS_API_H
#define _MDS_API_H


#include    <mds_global/mds_base_model.h>
#include    <mds_global/mds_mkt_packets.h>
#include    <mds_api/errors/mds_errors.h>
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
#define MDSAPI_CFG_DEFAULT_SECTION              "mds_client"
/** 默认的日志配置区段名称 */
#define MDSAPI_CFG_DEFAULT_SECTION_LOGGER       "log"

/** 默认的TCP行情订阅服务配置项名称 */
#define MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR         "tcpServer"
/** 默认的行情查询服务配置项名称 */
#define MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR         "qryServer"

/** UDP行情订阅服务配置项名称 (快照-频道1, 上海L1/L2快照) */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_SNAP1   "udpServer.Snap1"
/** UDP行情订阅服务配置项名称 (快照-频道2, 深圳L1/L2快照) */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_SNAP2   "udpServer.Snap2"

/** UDP行情订阅服务配置项名称 (逐笔-频道1, 上海逐笔成交) */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1   "udpServer.Tick1"
/** UDP行情订阅服务配置项名称 (逐笔-频道2, 深圳逐笔成交/逐笔委托) */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2   "udpServer.Tick2"

/** 默认的心跳间隔 (30 秒) */
#define MDSAPI_DEFAULT_HEARTBEAT_INTERVAL                   \
        GENERAL_CLI_DEFAULT_HEARTBEAT_INTERVAL
/** 默认的UDP连接的心跳间隔 (30 秒) */
#define MDSAPI_DEFAULT_UDP_HEARTBEAT_INTERVAL               \
        GENERAL_CLI_DEFAULT_UDP_HEARTBEAT_INTERVAL

/** 默认的证券代码列表等字符串分隔符 */
#define MDSAPI_DEFAULT_STRING_DELIM                         \
        ",;| \t\r\n"
/* -------------------------           */


/* ===================================================================
 * 已废弃的常量定义 (以下常量已废弃, 为了保持兼容而暂时保留)
 * =================================================================== */

/** UDP行情订阅服务配置项名称 (L1快照) @deprecated 已废弃, 效果等同于快照-频道1 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1                  \
        "udpServer.L1"
/** UDP行情订阅服务配置项名称 (L2快照) @deprecated 已废弃, 效果等同于快照-频道2 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2                  \
        "udpServer.L2"
/** UDP行情订阅服务配置项名称 (逐笔成交) @deprecated 已废弃, 效果等同于逐笔-频道1 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE          \
        "udpServer.TickTrade"
/** UDP行情订阅服务配置项名称 (逐笔委托) @deprecated 已废弃, 效果等同于逐笔-频道2 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER          \
        "udpServer.TickOrder"

/** 默认的UDP行情订阅服务配置项名称 @deprecated 已废弃, 效果等同于快照-频道1 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR                     \
        MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_SNAP1
/* -------------------------           */


/* ===================================================================
 * 常量定义, 枚举类型定义
 * =================================================================== */

/**
 * 通道类型定义
 */
typedef enum _eMdsApiChannelType {
    MDSAPI_CHANNEL_TYPE_TCP         = 11,       /**< TCP行情订阅通道 */
    MDSAPI_CHANNEL_TYPE_UDP         = 12,       /**< UDP行情组播通道 */
    MDSAPI_CHANNEL_TYPE_QUERY       = 13        /**< 行情查询通道 */
} eMdsApiChannelTypeT;
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * 客户端会话信息 (连接通道信息) 定义
 */
typedef SGeneralClientChannelT      MdsApiSessionInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_SESSION_INFO             \
        NULLOBJ_GENERAL_CLIENT_CHANNEL
/* -------------------------           */


/**
 * 客户端会话的连接通道组定义 (多个连接通道的集合)
 */
typedef SGeneralClientChannelGroupT MdsApiChannelGroupT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_CHANNEL_GROUP            \
        NULLOBJ_GENERAL_CLIENT_CHANNEL_GROUP
/* -------------------------           */


/**
 * Socket URI地址信息
 */
typedef SGeneralClientAddrInfoT     MdsApiAddrInfoT;


/* 结构体初始化值定义 */
#define NULLOBJ_MDSAPI_ADDR_INFO                \
        NULLOBJ_GENERAL_CLIENT_ADDR_INFO
/* -------------------------           */


/**
 * 远程主机配置信息
 */
typedef SGeneralClientRemoteCfgT    MdsApiRemoteCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_REMOTE_CFG               \
        NULLOBJ_GENERAL_CLIENT_REMOTE_CFG
/* -------------------------           */


/**
 * 主机地址列表的游标信息
 */
typedef SGeneralClientAddrCursorT   MdsApiAddrCursorT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_ADDR_CURSOR              \
        NULLOBJ_GENERAL_CLIENT_ADDR_CURSOR
/* -------------------------           */


/**
 * MDS行情订阅信息配置
 */
typedef MdsMktDataRequestReqBufT    MdsApiSubscribeInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_SUBSCRIBE_INFO           \
        NULLOBJ_MDS_MKT_DATA_REQUEST_REQ_BUF
/* -------------------------           */


/**
 * 完整的MDS客户端配置信息
 *
 * UDP行情组播频道说明:
 * - Snap1: 快照-频道1, 上海L1/L2快照
 * - Snap2: 快照-频道2, 深圳L1/L2快照
 * - Tick1: 逐笔-频道1, 上海逐笔成交
 * - Tick2: 逐笔-频道2, 深圳逐笔成交/逐笔委托
 */
typedef struct _MdsApiClientCfg {
    MdsApiRemoteCfgT        tcpChannelCfg;      /**< TCP行情订阅服务配置 */
    MdsApiRemoteCfgT        qryChannelCfg;      /**< 行情查询服务配置 */

    union {
        MdsApiRemoteCfgT    udpSnap1ChannelCfg; /**< 快照行情(频道1)组播服务配置 */
        MdsApiRemoteCfgT    udpL1ChannelCfg;    /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };
    union {
        MdsApiRemoteCfgT    udpSnap2ChannelCfg; /**< 快照行情(频道2)组播服务配置 */
        MdsApiRemoteCfgT    udpL2ChannelCfg;    /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };
    union {
        MdsApiRemoteCfgT    udpTick1ChannelCfg; /**< 逐笔数据(频道1)组播服务配置 */
        MdsApiRemoteCfgT    udpTradeChannelCfg; /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };
    union {
        MdsApiRemoteCfgT    udpTick2ChannelCfg; /**< 逐笔数据(频道2)组播服务配置 */
        MdsApiRemoteCfgT    udpOrderChannelCfg; /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };

    MdsApiSubscribeInfoT    subscribeInfo;      /**< TCP行情的行情订阅信息 */
} MdsApiClientCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_CLIENT_CFG               \
        {NULLOBJ_MDSAPI_REMOTE_CFG}, \
        {NULLOBJ_MDSAPI_REMOTE_CFG}, \
        {{NULLOBJ_MDSAPI_REMOTE_CFG}}, \
        {{NULLOBJ_MDSAPI_REMOTE_CFG}}, \
        {{NULLOBJ_MDSAPI_REMOTE_CFG}}, \
        {{NULLOBJ_MDSAPI_REMOTE_CFG}}, \
        {NULLOBJ_MDSAPI_SUBSCRIBE_INFO}
/* -------------------------           */


/**
 * MDS客户端运行时环境
 *
 * UDP行情组播频道说明:
 * - Snap1: 快照-频道1, 上海L1/L2快照
 * - Snap2: 快照-频道2, 深圳L1/L2快照
 * - Tick1: 逐笔-频道1, 上海逐笔成交
 * - Tick2: 逐笔-频道2, 深圳逐笔成交/逐笔委托
 */
typedef struct _MdsApiClientEnv {
    MdsApiSessionInfoT      tcpChannel;         /**< TCP行情订阅通道的会话信息 */
    MdsApiSessionInfoT      qryChannel;         /**< 行情查询通道的会话信息 */

    union {
        MdsApiSessionInfoT  udpSnap1Channel;    /**< 快照行情(频道1)组播通道的会话信息 */
        MdsApiSessionInfoT  udpL1Channel;       /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };
    union {
        MdsApiSessionInfoT  udpSnap2Channel;    /**< 快照行情(频道2)组播通道的会话信息 */
        MdsApiSessionInfoT  udpL2Channel;       /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };
    union {
        MdsApiSessionInfoT  udpTick1Channel;    /**< 逐笔数据(频道1)组播通道的会话信息 */
        MdsApiSessionInfoT  udpTradeChannel;    /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };
    union {
        MdsApiSessionInfoT  udpTick2Channel;    /**< 逐笔数据(频道2)组播通道的会话信息 */
        MdsApiSessionInfoT  udpOrderChannel;    /**< @deprecated 已废弃, 为了保持兼容而暂时保留 */
    };

    MdsApiChannelGroupT     udpChannelGroup;    /**< 用于管理多个行情组播会话的通道组信息 */
} MdsApiClientEnvT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_CLIENT_ENV               \
        {NULLOBJ_MDSAPI_SESSION_INFO}, \
        {NULLOBJ_MDSAPI_SESSION_INFO}, \
        {{NULLOBJ_MDSAPI_SESSION_INFO}}, \
        {{NULLOBJ_MDSAPI_SESSION_INFO}}, \
        {{NULLOBJ_MDSAPI_SESSION_INFO}}, \
        {{NULLOBJ_MDSAPI_SESSION_INFO}}, \
        {NULLOBJ_MDSAPI_CHANNEL_GROUP}
/* -------------------------           */


/* ===================================================================
 * 回调函数的函数原型定义
 * =================================================================== */

/**
 * 对接收到的消息进行处理的回调函数的函数原型定义
 *
 * @param   pSessionInfo        会话信息
 * @param   pMsgHead            消息头
 * @param   pMsgBody            消息体数据
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 成功
 * @retval  <0                  小于0, 处理失败 (负的错误号)
 *
 * @see     eMdsMsgTypeT
 * @see     MdsMktRspMsgBodyT
 * @see     MdsMktDataSnapshotT
 * @see     MdsL2TradeT
 * @see     MdsL2OrderT
 */
typedef int32   (*F_MDSAPI_ONMSG_T) (
                MdsApiSessionInfoT *pSessionInfo,
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
 * @see     eMdsMsgTypeT
 * @see     MdsMktRspMsgBodyT
 * @see     MdsQryStockStaticInfoRspT
 * @see     MdsQrySnapshotListRspT
 */
typedef int32   (*F_MDSAPI_ON_QRY_MSG_T) (
                MdsApiSessionInfoT *pSessionInfo,
                SMsgHeadT *pMsgHead,
                void *pMsgBody,
                MdsQryCursorT *pQryCursor,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 基于TCP协议的行情服务接口函数声明
 * =================================================================== */

/**
 * 连接并登录到行情服务器
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       channelType     通道类型
 * @param       pUri            URI地址 (e.g. tcp://127.0.0.1:5100)
 * @param       pUsername       用户名
 * @param       pPassword       密码
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
BOOL    MdsApi_Logon(
                MdsApiSessionInfoT *pOutSessionInfo,
                eMdsApiChannelTypeT channelType,
                const char *pUri,
                const char *pUsername,
                const char *pPassword,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 连接并登录到行情服务集群 (基于复制集的高可用集群)
 *
 * - 待解析的地址列表可是以空格、逗号或分号分割的地址列表字符串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同时也可以在每个地址之前, 为其指定对应的主机编号
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       channelType     通道类型
 * @param       pUriList        主机地址列表 (以空格、逗号或分号分割的地址列表字符串)
 * @param       pUsername       用户名
 * @param       pPassword       密码
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
BOOL    MdsApi_LogonReplicaSet(
                MdsApiSessionInfoT *pOutSessionInfo,
                eMdsApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 连接并登录到行情服务集群 (基于对等节点的行情集群)
 *
 * - 待解析的地址列表可是以空格、逗号或分号分割的地址列表字符串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同时也可以在每个地址之前, 为其指定对应的主机编号
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       channelType     通道类型
 * @param       pUriList        主机地址列表 (以空格、逗号或分号分割的地址列表字符串)
 * @param       pUsername       用户名
 * @param       pPassword       密码
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
BOOL    MdsApi_LogonPeerNodes(
                MdsApiSessionInfoT *pOutSessionInfo,
                eMdsApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 发送证券行情订阅消息, 并同步等待应答消息的返回 (仅适用于连接建立后的初次订阅)
 *
 * @param   pTcpChannel         会话信息
 * @param   pMktDataRequestReq  行情订阅请求信息
 * @param   pEntries            产品订阅列表
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_SyncSubscribeOnLogon(
                MdsApiSessionInfoT *pTcpChannel,
                const MdsMktDataRequestReqT *pMktDataRequestReq,
                const MdsMktDataRequestEntryT *pEntries);

/**
 * 以异步的方式发送证券行情实时订阅请求, 以重新订阅、追加订阅或删除订阅行情数据
 *
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 *
 * @param   pTcpChannel         会话信息
 * @param   pMktDataRequestReq  行情订阅请求信息
 * @param   pEntries            产品订阅列表
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_SubscribeMarketData(
                MdsApiSessionInfoT *pTcpChannel,
                const MdsMktDataRequestReqT *pMktDataRequestReq,
                const MdsMktDataRequestEntryT *pEntries);

/**
 * 根据字符串形式的证券代码列表订阅行情信息
 *
 * @note    为兼容之前的版本, 该接口无法指定 tickType 等订阅参数, 可以通过
 *          MdsApi_SetThreadSubscribeTickType 等接口来设置这些附加的订阅参数
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 * @note    订阅的数据类型 (dataTypes) 会以最后一次订阅为准, 所以每次都应该指定为所有待订阅
 *          的数据类型
 *
 * @param   pTcpChannel         会话信息
 * @param   pSecurityListStr    证券代码列表字符串
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "", 表示不订阅任何产品的行情
 *                              - 空指针 NULL, 表示订阅所有产品的行情
 * @param   pDelim              证券代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   exchangeId          证券代码所属的交易所代码 (如果证券代码没有 .SH 或 .SZ 后缀的话)
 * @param   mdProductType       行情类别 (股票(基金、债券)/指数/期权)
 * @param   subMode             订阅模式 (重新订阅/追加订阅/删除订阅)
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失败
 *
 * @see     MdsApi_SetThreadSubscribeTickType
 * @see     MdsApi_SetThreadSubscribeTickRebuildFlag
 * @see     MdsApi_SetThreadSubscribeTickExpireType
 * @see     MdsApi_SetThreadSubscribeRequireInitMd
 * @see     MdsApi_SetThreadSubscribeBeginTime
 */
BOOL    MdsApi_SubscribeByString(
                MdsApiSessionInfoT *pTcpChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/**
 * 根据字符串指针数组形式的证券代码列表订阅行情信息
 *
 * @note    为兼容之前的版本, 该接口无法指定 tickType 等订阅参数, 可以通过
 *          MdsApi_SetThreadSubscribeTickType 等接口来设置这些附加的订阅参数
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 * @note    订阅的数据类型 (dataTypes) 会以最后一次订阅为准, 所以每次都应该指定为所有待订阅
 *          的数据类型
 *
 * @param   pTcpChannel         会话信息
 * @param   ppSecurityArray     证券代码列表的指针数组
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空数组 (指针非空, 但 securityCount == 0), 表示不订阅任何产品的行情
 *                              - 空指针 NULL, 表示订阅所有产品的行情
 * @param   securityCount       证券代码数量
 * @param   exchangeId          证券代码所属的交易所代码 (如果证券代码没有 .SH 或 .SZ 后缀的话)
 * @param   mdProductType       行情类别 (股票(基金、债券)/指数/期权)
 * @param   subMode             订阅模式 (重新订阅/追加订阅/删除订阅)
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失败
 *
 * @see     MdsApi_SetThreadSubscribeTickType
 * @see     MdsApi_SetThreadSubscribeTickRebuildFlag
 * @see     MdsApi_SetThreadSubscribeTickExpireType
 * @see     MdsApi_SetThreadSubscribeRequireInitMd
 * @see     MdsApi_SetThreadSubscribeBeginTime
 */
BOOL    MdsApi_SubscribeByString2(
                MdsApiSessionInfoT *pTcpChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/**
 * 直接根据字符串形式的证券代码列表订阅行情, 并通过证券代码前缀来区分和识别所属市场
 *
 * @note    代码前缀仅对 pSecurityListStr 参数指定的证券代码生效, 只是为了方便区分证券代码
 *          所属的市场, 并不能直接通过代码前缀自动订阅所有匹配的股票
 * @note    为兼容之前的版本, 该接口无法指定 tickType 等订阅参数, 可以通过
 *          MdsApi_SetThreadSubscribeTickType 等接口来设置这些附加的订阅参数
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 * @note    订阅的数据类型 (dataTypes) 会以最后一次订阅为准, 所以每次都应该指定为所有待订阅
 *          的数据类型
 *
 * @param   pTcpChannel         会话信息
 * @param   pSecurityListStr    证券代码列表字符串
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "", 表示不订阅任何产品的行情
 *                              - 空指针 NULL, 表示订阅所有产品的行情
 * @param   pDelim              证券代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pSseCodePrefixes    以逗号或空格分隔的上海证券代码前缀列表, e.g.
 *                              - "6, 300, 301" 将匹配证券代码列表中所有以 '6' 或 '300'
 *                                或 '301' 起始的证券代码
 *                              - 若为NULL或空字符串, 则不会匹配任何证券代码
 *                              - 上海证券代码前缀参考:
 *                                  - "009, 01, 02, "               //国债
 *                                  - "10, 11, 12, 13, 18, 19, "    //债券 (企业债、可转债等)
 *                                  - "20, "                        //债券 (回购)
 *                                  - "5, "                         //基金
 *                                  - "6, "                         //A股
 *                                  - "000"                         //指数
 * @param   pSzseCodePrefixes   以逗号或空格分隔的深圳证券代码前缀列表
 *                              - 若为NULL或空字符串, 则不会匹配任何证券代码
 *                              - 证券代码前缀可以和上海相同, 此时匹配的证券代码会同时对上海
 *                                和深圳两个市场进行订阅
 *                              - 深圳证券代码前缀参考:
 *                                  - "00, "                        //股票
 *                                  - "10, 11, 12, 13, "            //债券
 *                                  - "15, 16, 17, 18, "            //基金
 *                                  - "30, "                        //创业板
 *                                  - "39"                          //指数
 * @param   mdProductType       行情类别 (股票(基金、债券)/指数/期权)
 * @param   subMode             订阅模式 (重新订阅/追加订阅/删除订阅)
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失败
 *
 * @see     MdsApi_SetThreadSubscribeTickType
 * @see     MdsApi_SetThreadSubscribeTickRebuildFlag
 * @see     MdsApi_SetThreadSubscribeTickExpireType
 * @see     MdsApi_SetThreadSubscribeRequireInitMd
 * @see     MdsApi_SetThreadSubscribeBeginTime
 */
BOOL    MdsApi_SubscribeByStringAndPrefixes(
                MdsApiSessionInfoT *pTcpChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const char *pSseCodePrefixes,
                const char *pSzseCodePrefixes,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/**
 * 根据字符串指针数组形式的证券代码列表订阅行情, 并通过证券代码前缀来区分和识别所属市场
 *
 * @note    代码前缀仅对 pSecurityListStr 参数指定的证券代码生效, 只是为了方便区分证券代码
 *          所属的市场, 并不能直接通过代码前缀自动订阅所有匹配的股票
 * @note    为兼容之前的版本, 该接口无法指定 tickType 等订阅参数, 可以通过
 *          MdsApi_SetThreadSubscribeTickType 等接口来设置这些附加的订阅参数
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 * @note    订阅的数据类型 (dataTypes) 会以最后一次订阅为准, 所以每次都应该指定为所有待订阅
 *          的数据类型
 *
 * @param   pTcpChannel         会话信息
 * @param   ppSecurityArray     证券代码列表的指针数组
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "", 表示不订阅任何产品的行情
 *                              - 空指针 NULL, 表示订阅所有产品的行情
 * @param   securityCount       证券代码数量
 * @param   pSseCodePrefixes    以逗号或空格分隔的上海证券代码前缀列表, e.g.
 *                              - "6, 300, 301" 将匹配证券代码列表中所有以 '6' 或 '300'
 *                                或 '301' 起始的证券代码
 *                              - 若为NULL或空字符串, 则不会匹配任何证券代码
 *                              - 上海证券代码前缀参考:
 *                                  - "009, 01, 02, "               //国债
 *                                  - "10, 11, 12, 13, 18, 19, "    //债券 (企业债、可转债等)
 *                                  - "20, "                        //债券 (回购)
 *                                  - "5, "                         //基金
 *                                  - "6, "                         //A股
 *                                  - "000"                         //指数
 * @param   pSzseCodePrefixes   以逗号或空格分隔的深圳证券代码前缀列表
 *                              - 若为NULL或空字符串, 则不会匹配任何证券代码
 *                              - 证券代码前缀可以和上海相同, 此时匹配的证券代码会同时对上海
 *                                和深圳两个市场进行订阅
 *                              - 深圳证券代码前缀参考:
 *                                  - "00, "                        //股票
 *                                  - "10, 11, 12, 13, "            //债券
 *                                  - "15, 16, 17, 18, "            //基金
 *                                  - "30, "                        //创业板
 *                                  - "39"                          //指数
 * @param   mdProductType       行情类别 (股票(基金、债券)/指数/期权)
 * @param   subMode             订阅模式 (重新订阅/追加订阅/删除订阅)
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失败
 *
 * @see     MdsApi_SetThreadSubscribeTickType
 * @see     MdsApi_SetThreadSubscribeTickRebuildFlag
 * @see     MdsApi_SetThreadSubscribeTickExpireType
 * @see     MdsApi_SetThreadSubscribeRequireInitMd
 * @see     MdsApi_SetThreadSubscribeBeginTime
 */
BOOL    MdsApi_SubscribeByStringAndPrefixes2(
                MdsApiSessionInfoT *pTcpChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                const char *pSseCodePrefixes,
                const char *pSzseCodePrefixes,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/**
 * 发送心跳消息
 *
 * @note    心跳消息不能发送的太过频繁, 需要控制不能超过每秒两次, 否则会带来延迟惩罚。
 *          建议使用和心跳时间相同的频率就可以 (例如: 5~30秒)
 *
 * @param   pSessionInfo        会话信息
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_SendHeartbeat(
                MdsApiSessionInfoT *pSessionInfo);

/**
 * 发送测试请求消息
 *
 * @note    测试请求消息的处理成本比较大, 如果发送太过频繁(超过每秒一次), 会带来额外的延迟惩罚
 *          处理。另外测试请求消息存在固有的毫秒级的发送成本, 需要尽量降低测试请求的发送频率。
 *          建议使用和心跳时间相同的频率就可以 (例如: 20~60秒)
 *
 * @param   pSessionInfo        会话信息
 * @param   pTestReqId          测试请求标识符 (C32, 可以为空)
 * @param   testReqIdSize       测试请求标识符的长度
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_SendTestRequest(
                MdsApiSessionInfoT *pSessionInfo,
                const char *pTestReqId,
                int32 testReqIdSize);

/**
 * 发送注销消息
 *
 * @param   pSessionInfo        会话信息
 * @param   isDestory           发送注销消息后是否立即释放相关资源
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_Logout(
                MdsApiSessionInfoT *pSessionInfo,
                BOOL isDestory);

/**
 * 直接断开与服务器的连接并释放会话数据
 *
 * @param   pSessionInfo        会话信息
 */
void    MdsApi_Destory(
                MdsApiSessionInfoT *pSessionInfo);

/**
 * 阻塞接收MDS行情消息, 并调用回调函数进行消息处理
 * 阻塞等待直到完整的消息接收完成或超时
 *
 * @param   pTcpChannel         会话信息
 * @param   timeoutMs           超时时间(毫秒)
 * @param   fnOnMsgCallback     进行消息处理的回调函数
 * @param   pCallbackParams     回调函数的参数
 * @return  大于等于0, 成功 (返回回调函数的返回值);
 *          小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由read()系统调用或回调函数fnOnMsgCallback返回的错误
 */
int32   MdsApi_WaitOnMsg(
                MdsApiSessionInfoT *pTcpChannel,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T fnOnMsgCallback,
                void *pCallbackParams);

/**
 * 阻塞接收MDS行情消息, 并调用回调函数进行消息处理 (可以处理压缩过的消息)
 *
 * - 与不带 Compressible 后缀的接口相比, 带 Compressible 后缀的接口会自动检测和处理压缩过的
 *   消息, 但也会因此带来微小的性能损失。
 * - 如果对延迟不是极端敏感的话, 可以直接使用带 Compressible 后缀的接口, 以方便兼容不同的模式。
 *
 * @param   pTcpChannel         会话信息
 * @param   timeoutMs           超时时间(毫秒)
 * @param   fnOnMsgCallback     进行消息处理的回调函数
 * @param   pCallbackParams     回调函数的参数
 * @return  大于等于0, 成功 (返回回调函数的返回值);
 *          小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由read()系统调用或回调函数fnOnMsgCallback返回的错误
 */
int32   MdsApi_WaitOnMsgCompressible(
                MdsApiSessionInfoT *pTcpChannel,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T fnOnMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 查询接口函数声明
 * =================================================================== */

/**
 * 获取API的发行版本号
 *
 * @return  API的发行版本号 (如: "0.15.3")
 */
const char *
        MdsApi_GetApiVersion();

/**
 * 查询证券行情快照
 *
 * @param       pQryChannel     会话信息
 * @param       exchangeId      交易所代码
 * @param       mdProductType   行情类别
 * @param       instrId         证券代码 (转换为整数类型的证券代码)
 * @param[out]  pRspBuf         用于输出查询结果的应答数据缓存
 *                              - 消息体的数据类型为L1快照 <code>MdsL1SnapshotT</code>
 * @retval      =0              查询成功
 * @retval      <0              查询失败 (负的错误号)
 * @exception   ENOENT          未检索到待查询的数据
 *
 * @see         MdsL1SnapshotT
 */
int32   MdsApi_QueryMktDataSnapshot(
                MdsApiSessionInfoT *pQryChannel,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                int32 instrId,
                MdsMktDataSnapshotT *pRspBuf);

/**
 * 批量查询行情快照
 *
 * @param   pQryChannel         会话信息
 * @param   pSecurityListStr    证券代码列表字符串
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "" 或 NULL, 表示查询所有产品的行情 (不包括指数和期权)
 * @param   pDelim              证券代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 代表无需过滤
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为L1快照 <code>MdsL1SnapshotT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     MdsL1SnapshotT
 */
int32   MdsApi_QuerySnapshotList(
                MdsApiSessionInfoT *pQryChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const MdsQrySnapshotListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 批量查询行情快照 (字符串指针数组形式的证券代码列表)
 *
 * @param   pQryChannel         会话信息
 * @param   ppSecurityArray     证券代码列表的指针数组
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空指针NULL或代码数量为0, 表示查询所有产品的行情 (不包括指数和期权)
 * @param   securityCount       证券代码数量
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 代表无需过滤
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为L1快照 <code>MdsL1SnapshotT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     MdsL1SnapshotT
 */
int32   MdsApi_QuerySnapshotList2(
                MdsApiSessionInfoT *pQryChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                const MdsQrySnapshotListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询(深圳)证券实时状态
 *
 * @param       pQryChannel     会话信息
 * @param       exchangeId      交易所代码
 * @param       mdProductType   行情类别
 * @param       instrId         证券代码 (转换为整数类型的证券代码)
 * @param[out]  pRspBuf         用于输出查询结果的应答数据缓存
 * @retval      =0              查询成功
 * @retval      <0              查询失败 (负的错误号)
 * @exception   ENOENT          未检索到待查询的数据
 *
 * @see         MdsSecurityStatusMsgT
 */
int32   MdsApi_QuerySecurityStatus(
                MdsApiSessionInfoT *pQryChannel,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                int32 instrId,
                MdsSecurityStatusMsgT *pRspBuf);

/**
 * 查询(上证)市场状态
 *
 * @param       pQryChannel     会话信息
 * @param       exchangeId      交易所代码
 * @param       mdProductType   行情类别
 * @param[out]  pRspBuf         用于输出查询结果的应答数据缓存
 * @retval      =0              查询成功
 * @retval      <0              查询失败 (负的错误号)
 * @exception   ENOENT          未检索到待查询的数据
 *
 * @see         MdsTradingSessionStatusMsgT
 */
int32   MdsApi_QueryTrdSessionStatus(
                MdsApiSessionInfoT *pQryChannel,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                MdsTradingSessionStatusMsgT *pRspBuf);

/**
 * 查询证券(股票/债券/基金)静态信息
 *
 * @param   pQryChannel         会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>MdsStockStaticInfoT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see         MdsStockStaticInfoT
 * @deprecated  已废弃, 推荐使用 MdsApi_QueryStockStaticInfoList 接口
 */
int32   MdsApi_QueryStockStaticInfo(
                MdsApiSessionInfoT *pQryChannel,
                const MdsQryStockStaticInfoFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 批量查询证券(股票/债券/基金)静态信息列表
 *
 * @param   pQryChannel         会话信息
 * @param   pSecurityListStr    证券代码列表字符串
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "" 或 NULL, 表示查询所有证券 (不包括指数和期权)
 * @param   pDelim              证券代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 代表无需过滤
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为证券静态信息 <code>MdsStockStaticInfoT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     MdsStockStaticInfoT
 */
int32   MdsApi_QueryStockStaticInfoList(
                MdsApiSessionInfoT *pQryChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const MdsQryStockStaticInfoListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 批量查询证券(股票/债券/基金)静态信息列表 (字符串指针数组形式的证券代码列表)
 *
 * @param   pQryChannel         会话信息
 * @param   ppSecurityArray     证券代码列表的指针数组
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空指针NULL或代码数量为0, 表示查询所有证券 (不包括指数和期权)
 * @param   securityCount       证券代码数量
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 代表无需过滤
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为证券静态信息 <code>MdsStockStaticInfoT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     MdsStockStaticInfoT
 */
int32   MdsApi_QueryStockStaticInfoList2(
                MdsApiSessionInfoT *pQryChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                const MdsQryStockStaticInfoListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 查询期权合约静态信息
 *
 * @param   pQryChannel         会话信息
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 将查询所有数据
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为 <code>MdsOptionStaticInfoT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see         MdsOptionStaticInfoT
 * @deprecated  已废弃, 推荐使用 MdsApi_QueryOptionStaticInfoList 接口
 */
int32   MdsApi_QueryOptionStaticInfo(
                MdsApiSessionInfoT *pQryChannel,
                const MdsQryOptionStaticInfoFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 批量查询期权合约静态信息列表
 *
 * @param   pQryChannel         会话信息
 * @param   pSecurityListStr    期权代码列表字符串
 *                              - 期权代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "" 或 NULL, 表示查询所有期权
 * @param   pDelim              期权代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 代表无需过滤
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为期权静态信息 <code>MdsOptionStaticInfoT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     MdsOptionStaticInfoT
 */
int32   MdsApi_QueryOptionStaticInfoList(
                MdsApiSessionInfoT *pQryChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const MdsQryOptionStaticInfoListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);

/**
 * 批量查询期权合约静态信息列表 (字符串指针数组形式的期权代码列表)
 *
 * @param   pQryChannel         会话信息
 * @param   ppSecurityArray     期权代码列表的指针数组
 *                              - 期权代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空指针NULL或代码数量为0, 表示查询所有期权
 * @param   securityCount       期权代码数量
 * @param   pQryFilter          查询过滤条件
 *                              - 传空指针或者将过滤条件初始化为0, 代表无需过滤
 * @param   fnQryMsgCallback    进行消息处理的回调函数
 *                              - 消息体的数据类型为期权静态信息 <code>MdsOptionStaticInfoT</code>
 * @param   pCallbackParams     回调函数的参数
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 *
 * @see     MdsOptionStaticInfoT
 */
int32   MdsApi_QueryOptionStaticInfoList2(
                MdsApiSessionInfoT *pQryChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                const MdsQryOptionStaticInfoListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T fnQryMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 密码修改接口函数声明
 * =================================================================== */

/**
 * 发送密码修改请求 (修改客户端登录密码)
 * 密码修改请求通过查询通道发送到MDS服务器, 并将采用同步请求/应答的方式直接返回处理结果
 *
 * @param       pQryChannel     会话信息
 * @param[in]   pChangePasswordReq
 *                              待发送的密码修改请求
 * @param[out]  pOutChangePasswordRsp
 *                              用于输出密码修改请求应答的缓存区
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (MDS错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   MdsApi_SendChangePasswordReq(
                MdsApiSessionInfoT *pQryChannel,
                const MdsChangePasswordReqT *pChangePasswordReq,
                MdsChangePasswordRspT *pOutChangePasswordRsp);
/* -------------------------           */


/* ===================================================================
 * 基于UDP协议的行情服务接口函数声明
 * =================================================================== */

/**
 * 建立与行情服务器的UDP(组播)连接
 *
 * @param[out]  pOutSessionInfo 输出会话信息
 * @param       pUri            URI地址 (e.g. udp-mcast://239.1.150.100:5300)
 * @param       pSocketOptions  套接字参数 (为空, 则会使用默认参数)
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_ConnectToUdpMcast(
                MdsApiSessionInfoT *pOutSessionInfo,
                const char *pUri,
                const SSocketOptionConfigT *pSocketOptions);

/**
 * 阻塞接收MDS-UDP行情消息, 并调用回调函数进行消息处理
 * 阻塞等待直到完整的消息接收完成或超时
 *
 * @param       pUdpChannel     会话信息
 * @param       timeoutMs       超时时间(毫秒)
 * @param       fnOnMsgCallback 进行消息处理的回调函数
 * @param       pCallbackParams 回调函数的参数
 * @return      大于等于0, 成功 (返回回调函数的返回值);
 *              小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由read()系统调用或回调函数fnOnMsgCallback返回的错误
 */
int32   MdsApi_WaitOnUdpMsg(
                MdsApiSessionInfoT *pUdpChannel,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T fnOnMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 完整的行情客户端环境的统一初始化和析构接口声明
 * =================================================================== */

/**
 * 完整的初始化行情客户端环境
 *
 * @param[out]  pOutCliEnv      输出行情客户端环境信息
 * @param       pCfgFile        配置文件路径
 * @param       pLoggerSection  日志记录器的配置区段名称
 * @param       pCfgSection     行情客户端配置区段名称
 * @param       pTcpAddrKey     TCP行情订阅地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pQryAddrKey     行情查询服务地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pUdpSnap1AddrKey
 *                              快照行情(频道1)组播地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pUdpSnap2AddrKey
 *                              快照行情(频道2)组播地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pUdpTick1AddrKey
 *                              逐笔数据(频道1)组播地址的配置项关键字 (为空或配置项未设置则不连接)
 * @param       pUdpTick2AddrKey
 *                              逐笔数据(频道2)组播地址的配置项关键字 (为空或配置项未设置则不连接)
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
 * @see         MdsApi_InitAllByConvention
 * @see         MdsApi_InitAllByCfgStruct
 */
BOOL    MdsApi_InitAll(
                MdsApiClientEnvT *pOutCliEnv,
                const char *pCfgFile,
                const char *pLoggerSection,
                const char *pCfgSection,
                const char *pTcpAddrKey,
                const char *pQryAddrKey,
                const char *pUdpSnap1AddrKey,
                const char *pUdpSnap2AddrKey,
                const char *pUdpTick1AddrKey,
                const char *pUdpTick2AddrKey);

/**
 * 按照默认的配置名称, 完整的初始化行情客户端环境
 *
 * 等价于下面的代码:
 * <code>
 *  return MdsApi_InitAll(pOutCliEnv, pCfgFile,
 *         MDSAPI_CFG_DEFAULT_SECTION_LOGGER, MDSAPI_CFG_DEFAULT_SECTION,
 *         MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR, MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR,
 *         MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_SNAP1, MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_SNAP2,
 *         MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1, MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2);
 * </code>
 *
 * @param[out]  pOutCliEnv      输出行情客户端环境信息
 * @param       pCfgFile        配置文件路径
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
 * @see         MdsApi_InitAll
 * @see         MdsApi_InitAllByCfgStruct
 */
BOOL    MdsApi_InitAllByConvention(
                MdsApiClientEnvT *pOutCliEnv,
                const char *pCfgFile);

/**
 * 按照配置信息结构体, 初始化客户端环境
 *
 * @note        与 MdsApi_InitAll 和 MdsApi_InitAllByConvention 接口有一处不同,
 *              MdsApi_InitAllByCfgStruct 接口不会自动初始化日志记录器, 需要在外面
 *              显式的调用 MdsApi_InitLogger 来初始化API的日志记录器
 *
 * @param[out]  pOutCliEnv      输出行情客户端环境信息
 * @param       pClientCfg      配置信息结构体
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
 * @see         MdsApi_InitAll
 * @see         MdsApi_InitAllByConvention
 */
BOOL    MdsApi_InitAllByCfgStruct(
                MdsApiClientEnvT *pOutCliEnv,
                const MdsApiClientCfgT *pClientCfg);

/**
 * 注销并关闭所有的行情客户端会话
 *
 * @param[out]  pCliEnv         行情客户端环境信息
 * @param       isDestory       是否立即释放相关资源
 * @return      TRUE 成功; FALSE 失败
 */
void    MdsApi_LogoutAll(MdsApiClientEnvT *pCliEnv, BOOL isDestory);

/**
 * 直接断开与服务器的连接并释放会话数据
 *
 * @param[out]  pCliEnv         行情客户端环境信息
 */
void    MdsApi_DestoryAll(
                MdsApiClientEnvT *pCliEnv);
/* -------------------------           */


/* ===================================================================
 * 基于配置文件的辅助接口函数声明
 * =================================================================== */

/**
 * 初始化日志记录器
 *
 * @param       pCfgFile        配置文件路径
 * @param       pLoggerSection  日志记录器的配置区段名称(为空则使用默认值)
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_InitLogger(
                const char *pCfgFile,
                const char *pLoggerSection);

/**
 * 重置线程级别的日志记录器名称
 *
 * @param   pLogSystemName  线程级别的日志系统名称
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_ResetThreadLoggerName(
                const char *pLogSystemName);

/**
 * 初始化基于TCP协议的行情订阅通道 (包括完整的配置解析、连接建立、登录和行情订阅过程)
 *
 * @param[out]  pTcpChannel     TCP行情订阅通道的会话信息
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     行情客户端配置区段名称(为空则使用默认值)
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
BOOL    MdsApi_InitTcpChannel(
                MdsApiSessionInfoT *pTcpChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/**
 * 初始化基于TCP协议的行情订阅通道 (包括完整的连接建立、登录和行情订阅过程)
 *
 * @param[out]  pTcpChannel     TCP行情订阅通道的会话信息
 * @param       pRemoteCfg      远程主机配置信息
 * @param       pSubscribeInfo  行情订阅配置信息
 *                              - 该参数可以为空, 为空则不会在登录后自动订阅行情
 *                              - @note 禁用自动订阅行情以后, 需要在登录后90秒内发起行情
 *                                订阅操作, 否则服务器端将主动关闭会话
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
BOOL    MdsApi_InitTcpChannel2(
                MdsApiSessionInfoT *pTcpChannel,
                const MdsApiRemoteCfgT *pRemoteCfg,
                const MdsApiSubscribeInfoT *pSubscribeInfo);

/**
 * 初始化行情查询通道 (包括完整的配置解析、连接建立和登录过程)
 *
 * @param[out]  pQryChannel     行情查询通道的会话信息
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     行情客户端配置区段名称(为空则使用默认值)
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
BOOL    MdsApi_InitQryChannel(
                MdsApiSessionInfoT *pQryChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/**
 * 初始化行情查询通道 (包括完整的连接建立和登录过程)
 *
 * @param[out]  pQryChannel     行情查询通道的会话信息
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
BOOL    MdsApi_InitQryChannel2(
                MdsApiSessionInfoT *pQryChannel,
                const MdsApiRemoteCfgT *pRemoteCfg);

/**
 * 初始化基于UDP协议的行情订阅通道 (包括完整的配置解析和连接建立过程)
 *
 * @param[out]  pUdpChannel     UDP行情订阅通道的会话信息
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     行情客户端配置区段名称(为空则使用默认值)
 * @param       pAddrKey        地址列表的配置项关键字(为空则使用默认值)
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   Others          由系统调用返回的错误
 */
BOOL    MdsApi_InitUdpChannel(
                MdsApiSessionInfoT *pUdpChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/**
 * 初始化基于UDP协议的行情订阅通道 (包括完整的连接建立过程)
 *
 * @param[out]  pUdpChannel     UDP行情订阅通道的会话信息
 * @param       pRemoteCfg      远程主机配置信息
 * @retval      TRUE            成功
 * @retval      FALSE           失败。此时 errno 将被设置, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因
 *
 * @exception   EINVAL          配置异常或传入参数非法
 * @exception   ENOENT          地址列表中没有找到有效的节点配置
 * @exception   Others          由系统调用返回的错误
 */
BOOL    MdsApi_InitUdpChannel2(
                MdsApiSessionInfoT *pUdpChannel,
                const MdsApiRemoteCfgT *pRemoteCfg);

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
int32   MdsApi_ParseAddrListString(
                const char *pUriList,
                MdsApiAddrInfoT *pOutAddrList,
                int32 addrListLength);

/**
 * 解析客户端配置文件
 *
 * @param       pCfgFile        配置文件路径
 * @param       pSection        配置区段名称
 * @param       pAddrKey        地址列表的配置项关键字
 * @param[out]  pOutRemoteCfg   输出远程主机配置信息
 * @param[out]  pOutSubscribeInfo
 *                              输出行情订阅信息
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_ParseConfigFromFile(
                const char *pCfgFile,
                const char *pSection,
                const char *pAddrKey,
                MdsApiRemoteCfgT *pOutRemoteCfg,
                MdsApiSubscribeInfoT *pOutSubscribeInfo);

/**
 * 解析客户端配置文件, 并可以指定是否允许配置项为空
 *
 * @param       pCfgFile        配置文件路径
 * @param       pSection        配置区段名称
 * @param       pAddrKey        地址列表的配置项关键字
 * @param[out]  pOutRemoteCfg   输出远程主机配置信息
 * @param[out]  pOutSubscribeInfo
 *                              输出行情订阅信息
 * @param       isRequiredCfg   是否必须配置 (是否允许配置项为空)
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_ParseConfigFromFile2(
                const char *pCfgFile,
                const char *pSection,
                const char *pAddrKey,
                MdsApiRemoteCfgT *pOutRemoteCfg,
                MdsApiSubscribeInfoT *pOutSubscribeInfo,
                BOOL isRequiredCfg);

/**
 * 按照默认的配置名称, 从配置文件中解析所有配置信息
 *
 * @param       pCfgFile        配置文件路径
 * @param[out]  pOutApiCfg      输出远程主机配置信息
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsApi_ParseAllConfig(
                const char *pCfgFile,
                MdsApiClientCfgT *pOutApiCfg);
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
BOOL    MdsApi_InitChannelGroup(
                MdsApiChannelGroupT *pChannelGroup);

/**
 * 销毁通道组信息 (同时关闭通道组下的所有连接)
 *
 * @param       pChannelGroup   通道组信息
 * @return      TRUE, 成功; FALSE 失败
 */
BOOL    MdsApi_DestoryChannelGroup(
                MdsApiChannelGroupT *pChannelGroup);

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
BOOL    MdsApi_AddToChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                MdsApiSessionInfoT *pChannel);

/**
 * 从通道组中删除连接
 *
 * @param       pChannelGroup   通道组信息
 * @param       pTargetChannel  待删除连接的连接信息
 * @return      TRUE, 成功; FALSE 失败
 */
BOOL    MdsApi_DeleteFromChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                MdsApiSessionInfoT *pTargetChannel);

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
MdsApiSessionInfoT *
        MdsApi_GetFromChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 index);

/**
 * 获取通道组中与指定Socket描述符相匹配的连接信息
 *
 * @param       pChannelGroup   通道组信息
 * @param       socketFd        Socket描述符
 * @return      连接信息
 */
MdsApiSessionInfoT *
        MdsApi_GetFromChannelGroupBySocket(
                MdsApiChannelGroupT *pChannelGroup,
                SPK_SOCKET socketFd);

/**
 * 返回通道组最近接收消息时间
 *
 * @param   pChannelGroup       通道组信息
 * @return  通道组最近接收消息时间(单位: 秒)
 */
int64   MdsApi_GetChannelGroupLastRecvTime(
                MdsApiChannelGroupT *pChannelGroup);

/**
 * 返回通道组最近发送消息时间
 *
 * @param   pChannelGroup       通道组信息
 * @return  通道组最近发送消息时间(单位: 秒)
 */
int64   MdsApi_GetChannelGroupLastSendTime(
                MdsApiChannelGroupT *pChannelGroup);

/**
 * 遍历通道组下的所有通道信息并执行回调函数
 *
 * @param       pChannelGroup   通道组信息
 * @param       fnCallback      待执行的回调函数
 * @param       pParams         回调函数的参数
 * @return      0, 成功; 小于 0, errno 取负
 */
int32   MdsApi_ForeachInChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 (*fnCallback)(MdsApiSessionInfoT *pChannel, void *pParams),
                void *pParams);

/**
 * 检测TCP通道组下各连接通道的读事件, 并调用回调函数进行消息处理
 *
 * @param       pChannelGroup   通道组信息
 * @param       timeoutMs       超时时间(毫秒)
 * @param       fnOnMsgCallback 进行消息处理的回调函数
 * @param       pCallbackParams 回调函数的参数
 * @param[out]  ppFailed        返回处理失败时所对应的连接信息
 *                              - 允许为空, 为空则忽略该参数
 *                              - 当因为超时(一定时间内没有数据)而返回时, 该参数的值为空
 * @return      大于等于0, 成功 (返回回调函数的返回值);
 *              小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由select/read系统调用或回调函数返回的错误
 */
int32   MdsApi_WaitOnTcpChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T fnOnMsgCallback,
                void *pCallbackParams,
                MdsApiSessionInfoT **ppFailed);

/**
 * 检测TCP通道组下各连接通道的读事件, 并调用回调函数进行消息处理 (可以处理压缩过的消息)
 *
 * - 与不带 Compressible 后缀的接口相比, 带 Compressible 后缀的接口会自动检测和处理压缩过的
 *   消息, 但也会因此带来微小的性能损失。
 * - 如果对延迟不是极端敏感的话, 可以直接使用带 Compressible 后缀的接口, 以方便兼容不同的模式。
 *
 * @param       pChannelGroup   通道组信息
 * @param       timeoutMs       超时时间(毫秒)
 * @param       fnOnMsgCallback 进行消息处理的回调函数
 * @param       pCallbackParams 回调函数的参数
 * @param[out]  ppFailed        返回处理失败时所对应的连接信息
 *                              - 允许为空, 为空则忽略该参数
 *                              - 当因为超时(一定时间内没有数据)而返回时, 该参数的值为空
 * @return      大于等于0, 成功 (返回回调函数的返回值);
 *              小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由select/read系统调用或回调函数返回的错误
 */
int32   MdsApi_WaitOnTcpChannelGroupCompressible(
                MdsApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T fnOnMsgCallback,
                void *pCallbackParams,
                MdsApiSessionInfoT **ppFailed);

/**
 * 检测UDP通道组下各连接通道的读事件, 并调用回调函数进行消息处理
 *
 * @param       pChannelGroup   通道组信息
 * @param       timeoutMs       超时时间(毫秒)
 * @param       fnOnMsgCallback 进行消息处理的回调函数
 * @param       pCallbackParams 回调函数的参数
 * @param[out]  ppFailed        返回处理失败时所对应的连接信息
 *                              - 允许为空, 为空则忽略该参数
 *                              - 当因为超时(一定时间内没有数据)而返回时, 该参数的值为空
 * @return      大于等于0, 成功 (返回回调函数的返回值);
 *              小于0, 失败 (负的错误号)
 *
 * @exception   ETIMEDOUT       超时
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由select/read系统调用或回调函数返回的错误
 */
int32   MdsApi_WaitOnUdpChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T fnOnMsgCallback,
                void *pCallbackParams,
                MdsApiSessionInfoT **ppFailed);
/* -------------------------           */


/* ===================================================================
 * 错误处理等辅助函数
 * =================================================================== */

/**
 * 设置当前线程登录MDS时使用的登录用户名
 * 不设置或者参数为空的话, 登录时会尝试使用配置文件中的配置
 *
 * @param   pUsername           登录用户名
 */
void    MdsApi_SetThreadUsername(
                const char *pUsername);

/**
 * 返回当前线程登录MDS时使用的登录用户名
 *
 * @return  登录用户名
 */
const char *
        MdsApi_GetThreadUsername();

/**
 * 设置当前线程登录MDS时使用的登录密码
 * 不设置或者参数为空的话, 登录时会尝试使用配置文件中的配置
 *
 * @param   pPassword           登录密码
 *                              - 支持通过密码前缀指定密码类型, 如 md5:PASSWORD, txt:PASSWORD
 */
void    MdsApi_SetThreadPassword(
                const char *pPassword);

/**
 * 设置当前线程登录TCP行情通道以后是否自动执行行情订阅操作
 *
 * <p>相关说明:
 * - 对于 InitAll/InitTcpChannel 这几个初始化接口, 默认情况下, 登录后会自动使用配置文件中
 *   的配置参数执行一次行情订阅操作, 可以通过该接口来设置线程级别的标志变量, 禁止登录以后自动
 *   执行行情订阅操作。
 * - beginTime 行情订阅参数, 仅在登录后的首次行情订阅时才可以使用, 禁用自动订阅行情以后, 就
 *   可以根据需要自行控制和发起首次行情订阅了。
 * - @note 禁用自动订阅行情以后, 需要在登录后90秒内发起行情订阅操作, 否则服务器端将主动关闭会话
 * </p>
 *
 * @param   isAutoSubscribeOnLogon
 *                              是否自动执行行情订阅操作
 *
 * @see     MdsApi_InitAll, MdsApi_InitAllByConvention, MdsApi_InitAllByCfgStruct
 * @see     MdsApi_InitTcpChannel, MdsApi_InitTcpChannel2
 */
void    MdsApi_SetThreadAutoSubscribeOnLogon(
                BOOL isAutoSubscribeOnLogon);

/**
 * 设置SubscribeByString接口默认使用的数据模式 (tickType)
 *
 * 为兼容之前的版本, SubscribeByString 系列的接口无法指定 tickType 订阅参数。
 * 可以通过该接口为其指定 tickType 参数, 后续的 SubscribeByString 调用都会使用该参数。
 *
 * @param   tickType            数据模式 @see eMdsSubscribedTickTypeT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 *
 * @see     MdsApi_SubscribeByString
 * @see     MdsApi_SubscribeByStringAndPrefixes
 */
void    MdsApi_SetThreadSubscribeTickType(
                int32 tickType);

/**
 * 设置SubscribeByString接口默认使用的逐笔数据的数据重建标识 (tickRebuildFlag, 标识是否订阅重建到的逐笔数据)
 *
 * @param   tickRebuildFlag     逐笔数据的数据重建标识 @see eMdsSubscribedTickRebuildFlagT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 *
 * @see     MdsApi_SubscribeByString
 * @see     MdsApi_SubscribeByStringAndPrefixes
 */
void    MdsApi_SetThreadSubscribeTickRebuildFlag(
                int32 tickRebuildFlag);

/**
 * 设置SubscribeByString接口默认使用的逐笔数据的过期时间类型 (tickExpireType)
 *
 * @param   tickExpireType      逐笔数据的过期时间类型 @see eMdsSubscribedTickExpireTypeT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 *
 * @see     MdsApi_SubscribeByString
 * @see     MdsApi_SubscribeByStringAndPrefixes
 */
void    MdsApi_SetThreadSubscribeTickExpireType(
                int32 tickExpireType);

/**
 * 设置SubscribeByString接口默认使用的初始快照订阅标志 (isRequireInitialMktData)
 *
 * @param   isRequireInitialMktData
 *                              是否需要推送已订阅产品的初始的行情快照
 *                              - @see MdsMktDataRequestReqT.isRequireInitialMktData
 *
 * @see     MdsApi_SubscribeByString
 * @see     MdsApi_SubscribeByStringAndPrefixes
 */
void    MdsApi_SetThreadSubscribeRequireInitMd(
                BOOL isRequireInitialMktData);

/**
 * 设置SubscribeByString接口默认使用的行情数据的起始时间 (beginTime)
 *
 * @param   beginTime           行情数据的起始时间
 *                              - -1: 从头开始获取
 *                              -  0: 从最新位置开始获取实时行情
 *                              - >0: 从指定的起始时间开始获取 (HHMMSS / HHMMSSsss)
 *                              - 当订阅模式为 Append/Delete/BatchDelete 时将忽略该参数
 *                              - @see MdsMktDataRequestReqT.beginTime
 *
 * @see     MdsApi_SubscribeByString
 * @see     MdsApi_SubscribeByStringAndPrefixes
 */
void    MdsApi_SetThreadSubscribeBeginTime(
                int32 beginTime);

/**
 * 设置客户端自定义的本地IP地址
 *
 * @param   pIpStr              点分十进制的IP地址字符串
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    MdsApi_SetCustomizedIp(
                const char *pIpStr);

/**
 * 设置客户端自定义的本地MAC地址
 *
 * @param   pMacStr             MAC地址字符串 (MAC地址格式 45:38:56:89:78:5A)
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    MdsApi_SetCustomizedMac(
                const char *pMacStr);

/**
 * 获取客户端自定义的本地IP
 *
 * @return  客户端自定义的本地IP
 */
const char *
        MdsApi_GetCustomizedIp();

/**
 * 获取客户端自定义的本地MAC
 *
 * @return  客户端自定义的本地MAC
 */
const char *
        MdsApi_GetCustomizedMac();

/**
 * 设置客户端自定义的本地设备序列号
 *
 * @param   pDriverId           设备序列号字符串
 * @return  TRUE 设置成功; FALSE 设置失败 (参数格式错误)
 */
BOOL    MdsApi_SetCustomizedDriverId(
                const char *pDriverId);

/**
 * 获取客户端自定义的本地设备序列号
 *
 * @return  客户端自定义的本地设备序列号
 */
const char *
        MdsApi_GetCustomizedDriverId();

/**
 * 获取通道最近接收消息时间
 *
 * @param   pSessionInfo        会话信息
 * @return  通道最近接收消息时间(单位: 秒)
 */
int64   MdsApi_GetLastRecvTime(
                const MdsApiSessionInfoT *pSessionInfo);

/**
 * 获取通道最近发送消息时间
 *
 * @param   pSessionInfo        会话信息
 * @return  通道最近发送消息时间(单位: 秒)
 */
int64   MdsApi_GetLastSendTime(
                const MdsApiSessionInfoT *pSessionInfo);

/**
 * 返回行情订阅通道是否还有更多已接收但尚未回调处理完成的数据
 *
 * @param   pTcpChannel         会话信息
 * @return  已接收到但尚未处理完成的数据长度
 * @note    当在回调函数里面调用时, 该接口返回的数据长度是包含本次回调数据的
 */
int32   MdsApi_HasMoreCachedData(
                const MdsApiSessionInfoT *pTcpChannel);

/**
 * 返回基于TCP协议的行情订阅通道是否已经连接且有效
 *
 * @param   pTcpChannel         会话信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    MdsApi_IsValidTcpChannel(
                const MdsApiSessionInfoT *pTcpChannel);

/**
 * 返回行情查询通道是否已经连接且有效
 *
 * @param   pQryChannel         会话信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    MdsApi_IsValidQryChannel(
                const MdsApiSessionInfoT *pQryChannel);

/**
 * 返回基于UDP协议的行情组播通道是否已经连接且有效
 *
 * @param   pUdpChannel         会话信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    MdsApi_IsValidUdpChannel(
                const MdsApiSessionInfoT *pUdpChannel);

/**
 * 返回通道组是否已经连接
 *
 * @param   pChannelGroup       通道组信息
 * @return  TRUE 已连接; FALSE 未连接或连接无效
 */
BOOL    MdsApi_IsValidChannelGroup(
                const MdsApiChannelGroupT *pChannelGroup);

/**
 * 返回当前线程最近一次API调用失败的错误号
 *
 * @return  错误号
 */
int32   MdsApi_GetLastError();

/**
 * 设置当前线程的API错误号
 *
 * @param   errCode             错误号
 */
void    MdsApi_SetLastError(
                int32 errCode);

/**
 * 返回错误号对应的错误信息
 *
 * @param   errCode             错误号
 * @return  错误号对应的错误信息
 */
const char *
        MdsApi_GetErrorMsg(
                int32 errCode);

/**
 * 返回消息头中的状态码所对应的错误信息
 *
 * @param   status              状态码
 * @param   detailStatus        明细状态码
 * @return  状态码所对应的错误信息
 */
const char *
        MdsApi_GetErrorMsg2(
                uint8 status,
                uint8 detailStatus);

/**
 * 返回指定错误码是否属于指定错误信息条目
 *
 * @param   errCode             错误编码
 * @param   pErr                错误信息条目
 * @return  TRUE 属于; FALSE 不属于
 */
BOOL    MdsApi_IsErrorOf(
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
BOOL    MdsApi_IsErrorOf2(
                uint8 status,
                uint8 detailStatus,
                const SErrMsgT *pErrMsg);

/**
 * 返回现货产品是否具有指定状态
 * 根据证券状态'securityStatus'字段判断 @see MdsStockStaticInfoT
 *
 * @param   pStockStaticInfo    现货产品信息
 * @param   status              指定的状态 @see eOesSecurityStatusT
 * @return  TRUE 具有指定的状态; FALSE 没有指定的状态
 */
BOOL    MdsApi_HasStockStatus(
                const MdsStockStaticInfoT *pStockStaticInfo,
                uint32 status);
/* -------------------------           */


/* ===================================================================
 * 辅助的订阅请求信息维护函数
 * =================================================================== */

/**
 * 设置SubscribeByString接口默认使用的数据模式 (tickType)
 *
 * 为兼容之前的版本, SubscribeByString 系列的接口无法指定 tickType 订阅参数。
 * 可以通过该接口为其指定 tickType 参数, 后续的 SubscribeByString 调用都会使用该参数。
 *
 * @param       tickType        数据模式 @see eMdsSubscribedTickTypeT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 *
 * @deprecated  等价于 MdsApi_SetThreadSubscribeTickType
 */
void    MdsHelper_SetTickTypeOnSubscribeByString(
                int32 tickType);

/**
 * 订阅信息的结构体操作函数 - 清空订阅信息中的产品列表
 *
 * @param   pSubscribeInfo      订阅信息
 */
void    MdsHelper_ClearSubscribeRequestEntries(
                MdsApiSubscribeInfoT *pSubscribeInfo);

/**
 * 订阅信息的结构体操作函数 - 设置订阅模式 (subMode)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   subMode             订阅模式 @see eMdsSubscribeModeT
 */
void    MdsHelper_SetSubscribeRequestMode(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsSubscribeModeT subMode);

/**
 * 订阅信息的结构体操作函数 - 设置数据模式 (tickType)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   tickType            数据模式 @see eMdsSubscribedTickTypeT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 */
void    MdsHelper_SetSubscribeRequestTickType(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                int32 tickType);

/**
 * 订阅信息的结构体操作函数 - 设置逐笔数据的数据重建标识 (tickRebuildFlag, 标识是否订阅重建到的逐笔数据)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   tickRebuildFlag     逐笔数据的数据重建标识 @see eMdsSubscribedTickRebuildFlagT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 */
void    MdsHelper_SetSubscribeRequestTickRebuildFlag(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                int32 tickRebuildFlag);

/**
 * 订阅信息的结构体操作函数 - 设置逐笔数据的过期时间类型 (tickExpireType)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   tickExpireType      逐笔数据的过期时间类型 @see eMdsSubscribedTickExpireTypeT
 *                              - 当订阅模式为追加订阅时, 如果该参数小于0, 将忽略该参数, 维持上一次订阅时的设置
 */
void    MdsHelper_SetSubscribeRequestTickExpireType(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                int32 tickExpireType);

/**
 * 订阅信息的结构体操作函数 - 设置初始快照订阅标志 (isRequireInitialMktData)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   isRequireInitialMktData
 *                              是否需要推送已订阅产品的初始的行情快照
 *                              - 当订阅模式为 Append/Delete/BatchDelete 时将忽略该参数
 */
void    MdsHelper_SetSubscribeRequestRequireInitMd(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                BOOL isRequireInitialMktData);

/**
 * 订阅信息的结构体操作函数 - 设置行情数据的起始时间 (beginTime)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   beginTime           行情数据的起始时间
 *                              - -1: 从头开始获取
 *                              -  0: 从最新位置开始获取实时行情
 *                              - >0: 从指定的起始时间开始获取 (HHMMSS / HHMMSSsss)
 *                              - 当订阅模式为 Append/Delete/BatchDelete 时将忽略该参数
 */
void    MdsHelper_SetSubscribeRequestBeginTime(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                int32 beginTime);

/**
 * 订阅信息的结构体操作函数 - 设置订阅的数据种类 (dataTypes)
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 */
void    MdsHelper_SetSubscribeRequestDataTypes(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                int32 dataTypes);

/**
 * 订阅信息的结构体操作函数 - 设置指定市场和证券类型的订阅标志
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   exchangeId          交易所代码  @see eMdsExchangeIdT
 *                              - MDS_EXCH_SSE, 上交所
 *                              - MDS_EXCH_SZSE, 深交所
 * @param   mdProductType       行情类别  @see eMdsMdProductTypeT
 *                              - MDS_MD_PRODUCT_TYPE_STOCK, 股票 (含债券、基金等现货产品)
 *                              - MDS_MD_PRODUCT_TYPE_INDEX, 指数
 *                              - MDS_MD_PRODUCT_TYPE_OPTION, 期权 (衍生品)
 * @param   subFlag             订阅标志 @see eMdsMktSubscribeFlagT
 *                              -  0: (Default) 根据订阅列表订阅产品行情
 *                              -  1: (All) 订阅该市场和证券类型下的所有产品行情
 *                              -  2: (Disable) 禁用该市场下的所有产品行情
 */
void    MdsHelper_SetSubscribeRequestSubFlag(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                eMdsMktSubscribeFlagT subFlag);

/**
 * 订阅信息的结构体操作函数 - 添加待订阅产品到订阅信息中
 *
 * @param   pSubscribeInfo      订阅信息
 * @param   exchangeId          交易所代码  @see eMdsExchangeIdT
 *                              - MDS_EXCH_SSE, 上交所
 *                              - MDS_EXCH_SZSE, 深交所
 * @param   mdProductType       行情类别  @see eMdsMdProductTypeT
 *                              - MDS_MD_PRODUCT_TYPE_STOCK, 股票 (含债券、基金等现货产品)
 *                              - MDS_MD_PRODUCT_TYPE_INDEX, 指数
 *                              - MDS_MD_PRODUCT_TYPE_OPTION, 期权 (衍生品)
 * @param   securityId          证券代码 (转换为整型数值的证券代码)
 * @return  大于等于0, 成功 (返回已添加到订阅列表中的产品数量);
 *          小于0, 失败 (负的错误号)
 */
int32   MdsHelper_AddSubscribeRequestEntry(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                int32 securityId);
/* -------------------------           */


/* ===================================================================
 * 用于校验API版本号是否匹配的标识函数定义
 * =================================================================== */

#define __MDSAPI_METHOD_IsApiVersionMatched_NAME2(VER)          \
        __MdsApi_IsApiVersionMatched__##VER

#define __MDSAPI_METHOD_IsApiVersionMatched_NAME(VER)           \
        __MDSAPI_METHOD_IsApiVersionMatched_NAME2(VER)

#define __MDSAPI_METHOD_IsApiVersionMatched                     \
        __MDSAPI_METHOD_IsApiVersionMatched_NAME(MDS_APPL_VER_VALUE)


/* 用于校验API版本号是否匹配的标识函数 (如果链接时报函数不存在错误, 请检查API的头文件与库文件是否一致) */
BOOL    __MDSAPI_METHOD_IsApiVersionMatched();
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
__MdsApi_CheckApiVersion() {
    /* 如果编译时报 IsApiVersionMatched 函数不存在错误, 请检查API的头文件与库文件是否一致 */
    if (__MDSAPI_METHOD_IsApiVersionMatched()
            && strcmp(MdsApi_GetApiVersion(), MDS_APPL_VER_ID) == 0) {
        return TRUE;
    }
    return FALSE;
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_API_H */
