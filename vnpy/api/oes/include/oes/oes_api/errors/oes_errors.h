/*
 * Copyright 2009-2014 the original author or authors.
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
 * @file    oes_errors.h
 *
 * 通信接口错误信息定义
 *
 * @version 0.15.6.13   2018/07/16
 *          - 新增错误码定义
 *              - 1029, 密码未改变 (OESERR_PASSWORD_UNCHANGED)
 *              - 1030, 非法的来源分类 (OESERR_ILLEGAL_SOURCE_TYPE)
 *              - 1031, 非法的加密类型 (OESERR_ILLEGAL_ENCRYPT_TYPE)
 *              - 1032, 非法的客户端设备序列号 (OESERR_ILLEGAL_DRIVER)
 *              - 1033, 无可用节点 (OESERR_NO_AVAILABLE_NODE)
 *              - 1271, 股东账户没有交易存托凭证的权限 (OESERR_NO_CDR_PERM)
 *              - 1272, 股东账户没有交易创新企业股票的权限 (OESERR_NO_INNOVATION_PERM)
 * @version 0.15.5.15   2018/08/14
 *          - 新增错误码定义
 *              - 1273, 非法的出入金转账类型 (OESERR_ILLEGAL_FUND_TRSF_TYPE)
 * @version 0.15.7.6    2018/10/16
 *          - 新增错误码定义
 *              - 1035, 非法的产品类型 (OESERR_ILLEGAL_PRODUCT_TYPE)
 *              - 1274, 股东账户没有交易沪伦通存托凭证的权限 (OESERR_NO_HLTCDR_PERM)
 * @version 0.15.8_RC3  2019/01/14
 *          - 调整错误描述
 *              - 1007, 非服务开放时间 (OESERR_NOT_TRADING_TIME)
 *              - 1022, 尚不支持或尚未开通此业务 (OESERR_NOT_SUPPORT)
 * @version 0.15.9      2019/03/12
 *          - 新增错误码定义
 *              - 1275, 股东账户没有交易科创板的权限 (OESERR_NO_KSH_PERM)
 *              - 1036, 未通过黑白名单检查 (OESERR_WBLIST_CHECK_FAILURE)
 *              - 1037, 集群编号不匹配 (OESERR_SET_NUM_MISMATCH)
 *              - 1038, 无此操作权限 (OESERR_NO_PERM)
 *              - 1276, 个股持仓比例超过限制 (OESERR_CUST_STK_POSITION_LIMIT)
 *              - 1277, 超出营业部委托流水号的有效范围 (OESERR_OUTOF_BRANCH_SEQ_RANGE)
 * @version 0.15.11     2020/05/29
 *          - 删除错误码定义
 *              - 1242, 出入金笔数超过限制 (OESERR_FUND_TRSF_CNT_LIMIT)
 *          - 调整错误描述
 *              - 1249, 不支持市价委托或账户无市价委托的交易权限 (OESERR_NO_MARKET_ORDER_PERM)
 *              - 1250, 股东账户没有交易创业板非注册制证券的权限 (OESERR_NO_GEM_PERM)
 *              - 1258, 股东账户没有交易货币ETF的权限 (OESERR_NO_CURRENCY_ETF_PERM)
 *          - 新增错误码定义
 *              - 1285, 股东账户没有交易债券ETF的权限 (OESERR_NO_BOND_ETF_PERM)
 *              - 1286, 股东账户没有交易黄金ETF的权限 (OESERR_NO_GOLD_ETF_PERM)
 *              - 1287, 股东账户没有交易商品期货ETF的权限 (OESERR_NO_COMMODITY_FUTURES_ETF_PERM)
 *              - 1288, 股东账户没有交易创业板注册制证券的权限 (OESERR_NO_GEM_REGISTRATION_PERM)
 *
 * @version 0.16        2019/01/18
 *          - 新增错误码定义
 *              - 1278, 结算单未确认 (OESERR_SETTLEMENT_NOT_CONFIRM)
 *              - 1279, 结算单重复确认 (OESERR_SETTLEMENT_REPEAT_CONFIRM)
 *              - 1280, 有未成交的卖出委托时禁止买入 (OESERR_FORBID_BUY_WITH_SELLING)
 *              - 1281, 有未成交的买入委托时禁止卖出 (OESERR_FORBID_SELL_WITH_BUYING)
 *              - 1282, 客户当日交易总量超出限制 (OESERR_INVESTOR_DAILY_TRADING_LIMIT)
 *              - 1283, 委托数量超出报备的单位委托数量限制 (OESERR_INVESTOR_ORDER_QTY_LIMIT)
 *              - 1284, 投资者未进行程序化交易报备 (OESERR_INVESTOR_NOT_FILING)
 *              - 1331, 非法的持仓类型 (OESERR_ILLEGAL_POSITION_TYPE)
 *              - 1332, 合约限制开仓 (OESERR_INSTR_LIMIT_OPEN_POSITION)
 *              - 1333, 客户权利仓持仓限额不足 (OESERR_LONG_POSITION_LIMIT)
 *              - 1334, 客户总持仓限额不足 (OESERR_TOTAL_POSITION_LIMIT)
 *              - 1335, 客户单日买入开仓限额不足 (OESERR_DAILY_BUY_OPEN_LIMIT)
 *              - 1336, 客户买入额度不足 (OESERR_INVESTOR_PURCHASE_LIMIT)
 *              - 1337, 券商总持仓限额不足 (OESERR_BROKER_POSITION_LIMIT)
 *              - 1338, 券商总保证金额度不足 (OESERR_BROKER_MARGIN_LIMIT)
 *              - 1339, 非法的标的锁定指令类型 (OESERR_ILLEGAL_UNDERLYING_LOCK_TYPE)
 *              - 1340, 禁止买入开仓 (OESERR_BUY_OPEN_LIMIT)
 *              - 1341, 禁止卖出平仓 (OESERR_SELL_CLOSE_LIMIT)
 *              - 1342, 禁止卖出开仓 (OESERR_SELL_OPEN_LIMIT)
 *              - 1343, 禁止买入平仓 (OESERR_BUY_CLOSE_LIMIT)
 *              - 1344, 禁止备兑开仓 (OESERR_COVERED_OPEN_LIMIT)
 *              - 1345, 禁止备兑平仓 (OESERR_COVERED_CLOSE_LIMIT)
 *              - 1346, 禁止标的锁定 (OESERR_UNDERLYING_FREEZE_LIMIT)
 *              - 1347, 禁止标的解锁 (OESERR_UNDERLYING_UNFREEZE_LIMIT)
 *              - 1348, 禁止期权行权 (OESERR_OPTION_EXERCISE_LIMIT)
 *              - 1349, 非行权日 (OESERR_ORDER_NOT_EXEC_DATE)
 * @version 0.16.0.3    2020/01/17
 *          - 删除错误码定义
 *              - 1284, 投资者未进行程序化交易报备 (OESERR_INVESTOR_NOT_FILING)
 * @version 0.16.0.5    2020/04/17
 *          - 新增错误码定义
 *              - 1284, 投资者未进行程序化交易报备 (OESERR_INVESTOR_NOT_FILING)
 * @since   2015/07/30
 */


#ifndef _OES_PROTOCOL_ERRORS_H
#define _OES_PROTOCOL_ERRORS_H


#include    <sutil/net/spk_errmsg_base_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * 通信接口错误定义表
 */
extern  SErrMsgT __SPK_DLL_IMPORT               __ERRS_oesApiErrors[];
/* -------------------------           */


/*
 * 通用错误定义
 */
/** 1001, 报文格式错误 */
#define OESERR_MSG_FORMAT                       (&__ERRS_oesApiErrors[0])
/** 1002, 当前主机不是主节点 */
#define OESERR_NOT_LEADER                       (&__ERRS_oesApiErrors[1])
/** 1003, 主存库操作失败 */
#define OESERR_SDB_FAILURE                      (&__ERRS_oesApiErrors[2])
/** 1004, 基础数据不匹配，无法更新数据 */
#define OESERR_UPDATE_EPERM                     (&__ERRS_oesApiErrors[3])
/** 1005, 协议版本不兼容 */
#define OESERR_INCOMPATIBLE_PROTOCOL_VERSION    (&__ERRS_oesApiErrors[4])
/** 1006, 数据不存在 */
#define OESERR_NOT_FOUND                        (&__ERRS_oesApiErrors[5])
/** 1007, 非服务开放时间 */
#define OESERR_NOT_TRADING_TIME                 (&__ERRS_oesApiErrors[6])
/** 1008, 非法的定位游标 */
#define OESERR_ILLEGAL_POSITION                 (&__ERRS_oesApiErrors[7])
/** 1009, 非法的客户端登录用户名称 */
#define OESERR_ILLEGAL_CLIENT_NAME              (&__ERRS_oesApiErrors[8])
/** 1010, 非法的证券代码 */
#define OESERR_ILLEGAL_SECURITY_ID              (&__ERRS_oesApiErrors[9])
/** 1011, 非法的客户代码 */
#define OESERR_ILLEGAL_CUST_ID                  (&__ERRS_oesApiErrors[10])
/** 1012, 非法的客户端类型 */
#define OESERR_ILLEGAL_CLIENT_TYPE              (&__ERRS_oesApiErrors[11])
/** 1013, 客户端已被禁用 */
#define OESERR_CLIENT_DISABLED                  (&__ERRS_oesApiErrors[12])
/** 1014, 客户端密码不正确 */
#define OESERR_CLIENT_PASSWORD_INVALID          (&__ERRS_oesApiErrors[13])
/** 1015, 客户端重复登录 */
#define OESERR_CLIENT_REPEATED_LOGON            (&__ERRS_oesApiErrors[14])
/** 1016, 客户端连接数量过多 */
#define OESERR_CLIENT_CONNECTIONS_LIMIT         (&__ERRS_oesApiErrors[15])
/** 1017, 客户端未经授权操作他人账户 */
#define OESERR_CLIENT_NOT_AUTHORIZED            (&__ERRS_oesApiErrors[16])
/** 1018, 数据超出修改范围 */
#define OESERR_DATA_OUTOF_RANGE                 (&__ERRS_oesApiErrors[17])
/** 1019, 非法的应用系统名称 */
#define OESERR_ILLEGAL_APPNAME                  (&__ERRS_oesApiErrors[18])
/** 1020, 请求条件有冲突 */
#define OESERR_CONFLICT_REQ_CONDITION           (&__ERRS_oesApiErrors[19])
/** 1021, 非法的客户端IP/MAC地址格式 */
#define OESERR_ILLEGAL_IP_MAC_FORMAT            (&__ERRS_oesApiErrors[20])
/** 1022, 尚不支持或尚未开通此业务 */
#define OESERR_NOT_SUPPORT                      (&__ERRS_oesApiErrors[21])
/** 1023, 非法的客户端环境号 */
#define OESERR_ILLEGAL_CLIENT_ENV_ID            (&__ERRS_oesApiErrors[22])
/** 1024, 交易所错误 */
#define OESERR_EXCHANGE_ERR                     (&__ERRS_oesApiErrors[23])
/** 1025, 主柜错误 */
#define OESERR_COUNTER_ERR                      (&__ERRS_oesApiErrors[24])
/** 1026, 流量超出限制范围 */
#define OESERR_TRAFFIC_CONTROL_OUTOF_RANGE      (&__ERRS_oesApiErrors[25])
/** 1027, 禁止使用API登录 */
#define OESERR_API_FORBIDDEN                    (&__ERRS_oesApiErrors[26])
/** 1028, 非法的私募基金产品代码 */
#define OESERR_ILLEGAL_PRIVATE_FUND_ID          (&__ERRS_oesApiErrors[27])
/** 1029, 密码未改变 */
#define OESERR_PASSWORD_UNCHANGED               (&__ERRS_oesApiErrors[28])
/** 1030, 非法的来源分类 */
#define OESERR_ILLEGAL_SOURCE_TYPE              (&__ERRS_oesApiErrors[29])
/** 1031, 非法的加密类型 */
#define OESERR_ILLEGAL_ENCRYPT_TYPE             (&__ERRS_oesApiErrors[30])
/** 1032, 非法的客户端设备序列号 */
#define OESERR_ILLEGAL_DRIVER                   (&__ERRS_oesApiErrors[31])
/** 1033, 无可用节点 */
#define OESERR_NO_AVAILABLE_NODE                (&__ERRS_oesApiErrors[32])
/** 1034, 密码强度不足 */
#define OESERR_PASSWORD_WEAK_STRENGTH           (&__ERRS_oesApiErrors[33])
/** 1035, 非法的产品类型 */
#define OESERR_ILLEGAL_PRODUCT_TYPE             (&__ERRS_oesApiErrors[34])
/** 1036, 未通过黑白名单检查 */
#define OESERR_WBLIST_CHECK_FAILURE             (&__ERRS_oesApiErrors[35])
/** 1037, 集群编号不匹配 */
#define OESERR_SET_NUM_MISMATCH                 (&__ERRS_oesApiErrors[36])
/** 1038, 无此操作权限 */
#define OESERR_NO_PERM                          (&__ERRS_oesApiErrors[37])
/* -------------------------           */


/*
 * 主柜台相关错误
 */
/** 1101, 登录柜台失败 */
#define OESERR_COUNTER_LOGON_FAILED             (&__ERRS_oesApiErrors[40])
/** 1102, 上报至柜台失败 */
#define OESERR_COUNTER_DLCR_FAILED              (&__ERRS_oesApiErrors[40 + 1])
/** 1103, 从柜台获取状态失败 */
#define OESERR_COUNTER_FETCH_FAILED             (&__ERRS_oesApiErrors[40 + 2])
/* -------------------------           */


/*
 * OES相关错误
 */
/** 1201, 非法的证券账户代码 */
#define OESERR_ILLEGAL_INV_ACCT_ID              (&__ERRS_oesApiErrors[60])
/** 1202, 非法的资金账户代码 */
#define OESERR_ILLEGAL_CASH_ACCT_ID             (&__ERRS_oesApiErrors[60 + 1])
/** 1203, 非法的出入金方向 */
#define OESERR_ILLEGAL_CASH_DIRECTION           (&__ERRS_oesApiErrors[60 + 2])
/** 1204, 非法的市场代码 */
#define OESERR_ILLEGAL_MARKET_ID                (&__ERRS_oesApiErrors[60 + 3])
/** 1205, 非法的证券类别 */
#define OESERR_ILLEGAL_SECURITY_TYPE            (&__ERRS_oesApiErrors[60 + 4])
/** 1206, 非法的买卖类型 */
#define OESERR_ILLEGAL_BUY_SELL_TYPE            (&__ERRS_oesApiErrors[60 + 5])
/** 1207, 非法的币种 */
#define OESERR_ILLEGAL_CURR_TYPE                (&__ERRS_oesApiErrors[60 + 6])
/** 1208, 非法的委托类型 */
#define OESERR_ILLEGAL_ORDER_TYPE               (&__ERRS_oesApiErrors[60 + 7])
/** 1209, 无效的账户状态 */
#define OESERR_ILLEGAL_ACCT_STATUS              (&__ERRS_oesApiErrors[60 + 8])
/** 1210, 未找到委托信息 */
#define OESERR_ORD_NOT_FOUND                    (&__ERRS_oesApiErrors[60 + 9])
/** 1211, 未找到持仓信息 */
#define OESERR_HOLDING_NOT_FOUND                (&__ERRS_oesApiErrors[60 + 10])
/** 1212, 未找到出入金流水 */
#define OESERR_FUND_TRSF_NOT_FOUND              (&__ERRS_oesApiErrors[60 + 11])
/** 1213, 流水号重复 */
#define OESERR_SEQNO_DUPLICATE                  (&__ERRS_oesApiErrors[60 + 12])
/** 1214, 当前时段不能报价 */
#define OESERR_ORDER_SESSION_CLOSE              (&__ERRS_oesApiErrors[60 + 13])
/** 1215, 没有操作权限 */
#define OESERR_ORDER_NO_RIGHT                   (&__ERRS_oesApiErrors[60 + 14])
/** 1216, 可用/可取资余额不足 */
#define OESERR_ORDER_CASH_NOT_ENOUGH            (&__ERRS_oesApiErrors[60 + 15])
/** 1217, 可用持仓不足 */
#define OESERR_ORDER_HOLDING_NOT_ENOUGH         (&__ERRS_oesApiErrors[60 + 16])
/** 1218, 委托数量不在合法区间内 */
#define OESERR_ORDER_QTY_RANGE                  (&__ERRS_oesApiErrors[60 + 17])
/** 1219, 非数量单位的整数倍 */
#define OESERR_ORDER_QTY_UNIT                   (&__ERRS_oesApiErrors[60 + 18])
/** 1220, 非法的PBU代码 */
#define OESERR_ILLEGAL_PBU_ID                   (&__ERRS_oesApiErrors[60 + 19])
/** 1221, 价格不在合法区间内 */
#define OESERR_ORDER_PRICE_RANGE                (&__ERRS_oesApiErrors[60 + 20])
/** 1222, 非价格单位的整数倍 */
#define OESERR_ORDER_PRICE_UNIT                 (&__ERRS_oesApiErrors[60 + 21])
/** 1223, 无涨停价市价委托失败 */
#define OESERR_ORDER_NO_CEIL_PRICE              (&__ERRS_oesApiErrors[60 + 22])
/** 1224, 当前时段不支持市价委托 */
#define OESERR_ORDER_DISAGREE_SESSION           (&__ERRS_oesApiErrors[60 + 23])
/** 1225, 无效的订单状态 */
#define OESERR_ORDER_ILLEGAL_STATUS             (&__ERRS_oesApiErrors[60 + 24])
/** 1226, 撤单信息与原始委托不符 */
#define OESERR_ORDER_MISMATCH_ORG               (&__ERRS_oesApiErrors[60 + 25])
/** 1227, 重复撤单 */
#define OESERR_ORDER_CANCEL_DUPLICATE           (&__ERRS_oesApiErrors[60 + 26])
/** 1228, 未通过限仓检查 */
#define OESERR_ORDER_HOLDING_QUOTA              (&__ERRS_oesApiErrors[60 + 27])
/** 1229, 未通过限购检查 */
#define OESERR_ORDER_CASH_QUOTA                 (&__ERRS_oesApiErrors[60 + 28])
/** 1230, 超过了ETF最大现金替代比例 */
#define OESERR_ORDER_ETF_CASH_RATIO             (&__ERRS_oesApiErrors[60 + 29])
/** 1231, 未定义1 */
#define OESERR_UNDEFINE1                        (&__ERRS_oesApiErrors[60 + 30])
/** 1232, 证券停牌 */
#define OESERR_ORDER_INSTR_SUSP                 (&__ERRS_oesApiErrors[60 + 31])
/** 1233, 合约限制开仓 */
#define OESERR_ORDER_INSTR_OPEN_LIMIT           (&__ERRS_oesApiErrors[60 + 32])
/** 1234, 当日累计申购或赎回数量超过限额 */
#define OESERR_ORDER_CRE_RED_QUOTA              (&__ERRS_oesApiErrors[60 + 33])
/** 1235, 当日累计净申购或净赎回数量超过限额 */
#define OESERR_ORDER_NET_CRE_RED_QUOTA          (&__ERRS_oesApiErrors[60 + 34])
/** 1236, 找不到前收盘价 */
#define OESERR_ORDER_NO_PREV_CLOSE              (&__ERRS_oesApiErrors[60 + 35])
/** 1237, 超过报撤比限制 */
#define OESERR_ORDER_EXCEED_CANCEL_RATE         (&__ERRS_oesApiErrors[60 + 36])
/** 1238, 委托请求过于频繁 */
#define OESERR_ORDER_REQ_TOO_OFTEN              (&__ERRS_oesApiErrors[60 + 37])
/** 1239, 非法的出入金转账金额 */
#define OESERR_ILLEGAL_FUND_TRSF_AMOUNT         (&__ERRS_oesApiErrors[60 + 38])
/** 1240, 重复的认购委托 */
#define OESERR_SUBSCRIPTION_DUPLICATE           (&__ERRS_oesApiErrors[60 + 39])
/** 1241, 认购委托份数超过认购额度 */
#define OESERR_SUBSCRIPTION_QUOTA_EXCEED        (&__ERRS_oesApiErrors[60 + 40])
/** 1242, 未定义2 */
#define OESERR_UNDEFINE2                        (&__ERRS_oesApiErrors[60 + 41])
/** 1243, 禁止同时做多笔出入金 */
#define OESERR_FORBID_CONCURRENT_FUND_TRSF      (&__ERRS_oesApiErrors[60 + 42])
/** 1244, 非法的新股配号、中签记录类型 */
#define OESERR_ILLEGAL_LOT_TYPE                 (&__ERRS_oesApiErrors[60 + 43])
/** 1245, 限制股东账户进行买交易 */
#define OESERR_BUY_LIMIT                        (&__ERRS_oesApiErrors[60 + 44])
/** 1246, 限制股东账户进行卖交易 */
#define OESERR_SELL_LIMIT                       (&__ERRS_oesApiErrors[60 + 45])
/** 1247, 限制股东账户进行逆回购交易 */
#define OESERR_PLEDGED_REPO_LIMIT               (&__ERRS_oesApiErrors[60 + 46])
/** 1248, 限制股东账户进行新股认购交易 */
#define OESERR_SUBSCRIPTION_LIMIT               (&__ERRS_oesApiErrors[60 + 47])
/** 1249, 不支持市价委托或账户无市价委托的交易权限 */
#define OESERR_NO_MARKET_ORDER_PERM             (&__ERRS_oesApiErrors[60 + 48])
/** 1250, 股东账户没有交易创业板非注册制证券的权限 */
#define OESERR_NO_GEM_PERM                      (&__ERRS_oesApiErrors[60 + 49])
/** 1251, 股东账户没有交易分级基金的权限 */
#define OESERR_NO_STRUCTURED_FUND_PERM          (&__ERRS_oesApiErrors[60 + 50])
/** 1252, 股东账户没有债券合格投资者的权限 */
#define OESERR_NO_BOND_QUALIFIED_INV_PERM       (&__ERRS_oesApiErrors[60 + 51])
/** 1253, 客户风险评级低于交易证券需求的风险等级 */
#define OESERR_HIGHER_RISK_LEVEL_REQUIRED       (&__ERRS_oesApiErrors[60 + 52])
/** 1254, 股东账户没有交易风险警示证券的权限 */
#define OESERR_NO_RISK_WARNING_PERM             (&__ERRS_oesApiErrors[60 + 53])
/** 1255, 股东账户没有交易退市整理证券的权限 */
#define OESERR_NO_DELISTING_PERM                (&__ERRS_oesApiErrors[60 + 54])
/** 1256, 股东账户没有交易单市场ETF的权限 */
#define OESERR_NO_SINGLE_MARKET_ETF_PERM        (&__ERRS_oesApiErrors[60 + 55])
/** 1257, 股东账户没有交易跨市场ETF的权限 */
#define OESERR_NO_CROSS_MARKET_ETF_PERM         (&__ERRS_oesApiErrors[60 + 56])
/** 1258, 股东账户没有交易货币ETF的权限 */
#define OESERR_NO_CURRENCY_ETF_PERM             (&__ERRS_oesApiErrors[60 + 57])
/** 1259, 股东账户没有交易跨境ETF的权限 */
#define OESERR_NO_CROSS_BORDER_ETF_PERM         (&__ERRS_oesApiErrors[60 + 58])
/** 1260, 仅允许合格投资者投资该证券 */
#define OESERR_QUALIFIED_INVESTOR_ONLY          (&__ERRS_oesApiErrors[60 + 59])
/** 1261, 仅允许合格机构投资者投资该证券 */
#define OESERR_QUALIFIED_INSTITUTION_ONLY       (&__ERRS_oesApiErrors[60 + 60])
/** 1262, 出入金执行异常，待人工干预 */
#define OESERR_FUND_TRSF_WAIT_MANUAL_INTERVENE  (&__ERRS_oesApiErrors[60 + 61])
/** 1263, 交易日不在证券的发行期内 */
#define OESERR_NOT_ISSUE_DATE                   (&__ERRS_oesApiErrors[60 + 62])
/** 1264, 该ETF禁止申购 */
#define OESERR_ETF_FORBID_CREATION              (&__ERRS_oesApiErrors[60 + 63])
/** 1265, 该ETF禁止赎回 */
#define OESERR_ETF_FORBID_REDEMPTION            (&__ERRS_oesApiErrors[60 + 64])
/** 1266, 限制股东账户进行撤指定 */
#define OESERR_RECALL_DESIGNATION_LIMIT         (&__ERRS_oesApiErrors[60 + 65])
/** 1267, 限制股东账户进行转托管 */
#define OESERR_DESIGNATION_LIMIT                (&__ERRS_oesApiErrors[60 + 66])
/** 1268, 机构客户/主柜业务不支持银行转帐 */
#define OESERR_NOT_SUPPORT_BANK_TRSF            (&__ERRS_oesApiErrors[60 + 67])
/** 1269, 禁止私募基金产品交易此证券 */
#define OESERR_SECURITY_IN_FUND_BLACKLIST       (&__ERRS_oesApiErrors[60 + 68])
/** 1270, 禁止客户交易此证券 */
#define OESERR_SECURITY_IN_CUST_BLACKLIST       (&__ERRS_oesApiErrors[60 + 69])
/** 1271, 股东账户没有交易存托凭证的权限 */
#define OESERR_NO_CDR_PERM                      (&__ERRS_oesApiErrors[60 + 70])
/** 1272, 股东账户没有交易创新企业股票的权限 */
#define OESERR_NO_INNOVATION_PERM               (&__ERRS_oesApiErrors[60 + 71])
/** 1273, 非法的出入金转账类型 */
#define OESERR_ILLEGAL_FUND_TRSF_TYPE           (&__ERRS_oesApiErrors[60 + 72])
/** 1274, 股东账户没有交易沪伦通存托凭证的权限 */
#define OESERR_NO_HLTCDR_PERM                   (&__ERRS_oesApiErrors[60 + 73])
/** 1275, 股东账户没有交易科创板的权限 */
#define OESERR_NO_KSH_PERM                      (&__ERRS_oesApiErrors[60 + 74])
/** 1276, 个股持仓比例超过限制 */
#define OESERR_CUST_STK_POSITION_LIMIT          (&__ERRS_oesApiErrors[60 + 75])
/** 1277, 营业部委托流水号超出有效范围 */
#define OESERR_OUTOF_BRANCH_SEQ_RANGE           (&__ERRS_oesApiErrors[60 + 76])
/** 1278, 结算单未确认 */
#define OESERR_SETTLEMENT_NOT_CONFIRM           (&__ERRS_oesApiErrors[60 + 77])
/** 1279, 结算单重复确认 */
#define OESERR_SETTLEMENT_REPEAT_CONFIRM        (&__ERRS_oesApiErrors[60 + 78])
/** 1280, 有未成交的卖出委托时禁止买入 */
#define OESERR_FORBID_BUY_WITH_SELLING          (&__ERRS_oesApiErrors[60 + 79])
/** 1281, 有未成交的买入委托时禁止卖出 */
#define OESERR_FORBID_SELL_WITH_BUYING          (&__ERRS_oesApiErrors[60 + 80])
/** 1282, 客户当日交易总量超出限制 */
#define OESERR_INVESTOR_DAILY_TRADING_LIMIT     (&__ERRS_oesApiErrors[60 + 81])
/** 1283, 委托数量超出报备的单笔委托数量限制 */
#define OESERR_INVESTOR_ORDER_QTY_LIMIT         (&__ERRS_oesApiErrors[60 + 82])
/** 1284, 投资者未进行程序化交易报备 */
#define OESERR_INVESTOR_NOT_FILING              (&__ERRS_oesApiErrors[60 + 83])
/** 1285, 股东账户没有交易债券ETF的权限 */
#define OESERR_NO_BOND_ETF_PERM                 (&__ERRS_oesApiErrors[60 + 84])
/** 1286, 股东账户没有交易黄金ETF的权限 */
#define OESERR_NO_GOLD_ETF_PERM                 (&__ERRS_oesApiErrors[60 + 85])
/** 1287, 股东账户没有交易商品期货ETF的权限 */
#define OESERR_NO_COMMODITY_FUTURES_ETF_PERM    (&__ERRS_oesApiErrors[60 + 86])
/** 1288, 股东账户没有交易创业板注册制证券的权限 */
#define OESERR_NO_GEM_REGISTRATION_PERM         (&__ERRS_oesApiErrors[60 + 87])
/* -------------------------           */


/*
 * 期权业务新增的错误号
 */
/** 1331, 非法的持仓类型 */
#define OESERR_ILLEGAL_POSITION_TYPE            (&__ERRS_oesApiErrors[160])
/** 1332, 合约限制开仓 */
#define OESERR_INSTR_LIMIT_OPEN_POSITION        (&__ERRS_oesApiErrors[160 + 1])
/** 1333, 客户权利仓持仓限额不足 */
#define OESERR_LONG_POSITION_LIMIT              (&__ERRS_oesApiErrors[160 + 2])
/** 1334, 客户总持仓限额不足 */
#define OESERR_TOTAL_POSITION_LIMIT             (&__ERRS_oesApiErrors[160 + 3])
/** 1335, 客户单日买入开仓限额不足 */
#define OESERR_DAILY_BUY_OPEN_LIMIT             (&__ERRS_oesApiErrors[160 + 4])
/** 1336, 客户买入额度不足 (限购) */
#define OESERR_INVESTOR_PURCHASE_LIMIT          (&__ERRS_oesApiErrors[160 + 5])
/** 1337, 券商总持仓限额不足 */
#define OESERR_BROKER_POSITION_LIMIT            (&__ERRS_oesApiErrors[160 + 6])
/** 1338, 券商总保证金额度不足 */
#define OESERR_BROKER_MARGIN_LIMIT              (&__ERRS_oesApiErrors[160 + 7])
/** 1339, 非法的标的锁定指令类型 */
#define OESERR_ILLEGAL_UNDERLYING_LOCK_TYPE     (&__ERRS_oesApiErrors[160 + 8])
/** 1340, 禁止买入开仓 */
#define OESERR_BUY_OPEN_LIMIT                   (&__ERRS_oesApiErrors[160 + 9])
/** 1341, 禁止卖出平仓 */
#define OESERR_SELL_CLOSE_LIMIT                 (&__ERRS_oesApiErrors[160 + 10])
/** 1342, 禁止卖出开仓 */
#define OESERR_SELL_OPEN_LIMIT                  (&__ERRS_oesApiErrors[160 + 11])
/** 1343, 禁止买入平仓 */
#define OESERR_BUY_CLOSE_LIMIT                  (&__ERRS_oesApiErrors[160 + 12])
/** 1344, 禁止备兑开仓 */
#define OESERR_COVERED_OPEN_LIMIT               (&__ERRS_oesApiErrors[160 + 13])
/** 1345, 禁止备兑平仓 */
#define OESERR_COVERED_CLOSE_LIMIT              (&__ERRS_oesApiErrors[160 + 14])
/** 1346, 禁止标的锁定 */
#define OESERR_UNDERLYING_FREEZE_LIMIT          (&__ERRS_oesApiErrors[160 + 15])
/** 1347, 禁止标的解锁 */
#define OESERR_UNDERLYING_UNFREEZE_LIMIT        (&__ERRS_oesApiErrors[160 + 16])
/** 1348, 禁止期权行权 */
#define OESERR_OPTION_EXERCISE_LIMIT            (&__ERRS_oesApiErrors[160 + 17])
/** 1349, 非行权日 */
#define OESERR_ORDER_NOT_EXEC_DATE              (&__ERRS_oesApiErrors[160 + 18])
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_PROTOCOL_ERRORS_H */
