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
 *              - 1250, 股东账户没有交易创业板核准制证券的权限 (OESERR_NO_GEM_PERM)
 *              - 1258, 股东账户没有交易货币ETF的权限 (OESERR_NO_CURRENCY_ETF_PERM)
 *          - 新增错误码定义
 *              - 1285, 股东账户没有交易债券ETF的权限 (OESERR_NO_BOND_ETF_PERM)
 *              - 1286, 股东账户没有交易黄金ETF的权限 (OESERR_NO_GOLD_ETF_PERM)
 *              - 1287, 股东账户没有交易商品期货ETF的权限 (OESERR_NO_COMMODITY_FUTURES_ETF_PERM)
 *              - 1288, 股东账户没有交易创业板注册制证券的权限 (OESERR_NO_GEM_REGISTRATION_PERM)
 * @version 0.15.11.12  2020/09/30
 *              - 1289, 股东账户没有交易可转换公司债券的权限 (OESERR_NO_CONVERTIBLE_BOND_PERM)
 *              - 1290, 股东账户没有交易基础设施基金的权限 (OESERR_NO_INFRASTRUCTURE_FUND_PERM)
 * @version 0.15.11.15  2020/11/20
 *              - 重命名错误码的宏定义
 *                  - 1290, 股东账户没有交易基础设施基金的权限 (OESERR_NO_INFRASTRUCTURE_FUND_PERM => OESERR_NO_REITS_PERM)
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
 * @version 0.17        2020/09/16
 *          - 新增错误码定义
 *              - 1039, 非法的指令类型 (OESERR_ILLEGAL_CMD_TYPE)
 *              - 1291, 限制入金 (OESERR_DEPOSIT_LIMIT)
 *              - 1292, 限制出金 (OESERR_WITHDRAW_LIMIT)
 *              - 1401, 保证金可用余额不足 (OESERR_MARGIN_NOT_ENOUGH)
 *              - 1402, 可用还款资金不足 (OESERR_REPAY_CASH_NOT_ENOUGH)
 *              - 1403, 客户可用两融总额度不足 (OESERR_CUST_CREDIT_TRADE_QUOTA)
 *              - 1404, 券商可用两融总额度不足 (OESERR_BROKER_CREDIT_TRADE_QUOTA)
 *              - 1405, 客户可用融资额度不足 (OESERR_CUST_MARGIN_BUY_QUOTA)
 *              - 1406, 券商可用融资额度不足 (OESERR_BROKER_MARGIN_BUY_QUOTA)
 *              - 1407, 客户可用融券额度不足 (OESERR_CUST_SHORT_SELL_QUOTA)
 *              - 1408, 券商可用融券额度不足 (OESERR_BROKER_SHORT_SELL_QUOTA)
 *              - 1409, 可用融资头寸不足 (OESERR_CASH_POSITION_NOT_ENOUGH)
 *              - 1410, 可用融券头寸不足 (OESERR_SECURITY_POSITION_NOT_ENOUGH)
 *              - 1411, 无可用融资头寸 (OESERR_CASH_GROUP_NOT_FOUND)
 *              - 1412, 无可用融券头寸 (OESERR_NO_SECURITY_POSITION)
 *              - 1413, 非法的头寸性质 (OESERR_ILLEGAL_CASH_GROUP_PROPERTY)
 *              - 1414, 单笔委托融资金额超上限 (OESERR_ORD_MARGIN_BUY_CEILING)
 *              - 1415, 单笔委托融券规模超上限 (OESERR_ORD_SHORT_SELL_CEILING)
 *              - 1416, 禁止担保品转入 (OESERR_COLLATERAL_TRANSFER_IN_LIMIT)
 *              - 1417, 禁止担保品转出 (OESERR_COLLATERAL_TRANSFER_OUT_LIMIT)
 *              - 1418, 禁止融资买入 (OESERR_MARGIN_BUY_LIMIT)
 *              - 1419, 禁止卖券还款 (OESERR_REPAY_MARGIN_BY_SELL_LIMIT)
 *              - 1420, 禁止直接还款 (OESERR_REPAY_MARGIN_DIRECT_LIMIT)
 *              - 1421, 禁止融券卖出 (OESERR_SHORT_SELL_LIMIT)
 *              - 1422, 禁止买券还券 (OESERR_REPAY_STOCK_BY_BUY_LIMIT)
 *              - 1423, 禁止直接还券 (OESERR_REPAY_STOCK_DIRECT_LIMIT)
 *              - 1424, 禁止董监高或大股东的融资融券交易 (OESERR_CHIEF_OR_MAJOR_CREDIT_LIMIT)
 *              - 1425, 禁止提交限售股份为担保物 (OESERR_RESTRICTED_STOCKS_TO_COLLATERAL)
 *              - 1426, 禁止个人投资者提交解除限售存量股份为担保物 (OESERR_INDIVIDUAL_RESTRICTED_STOCKS_LIFTED_TO_COLLATERAL)
 *              - 1427, 禁止大小非开展该证券的融资融券交易 (OESERR_NON_TRADABLE_SHARE_CREDIT_LIMIT)
 *              - 1428, 禁止其他股东角色开展该证券的融资融券交易 (OESERR_OTHER_ROLES_CREDIT_LIMIT)
 *              - 1429, 无效的担保品状态 (OESERR_ILLEGAL_COLLATERAL_STATUS)
 *              - 1430, 非担保证券 (OESERR_NOT_COLLATERAL)
 *              - 1431, 非融资标的证券 (OESERR_NOT_MARGIN_BUY_UNDERLYING)
 *              - 1432, 非融券标的证券 (OESERR_NOT_SHORT_SELL_UNDERLYING)
 *              - 1433, 非融资负债 (OESERR_NOT_MARGIN_BUY_DEBT)
 *              - 1434, 非融券负债 (OESERR_NOT_SHORT_SELL_DEBT)
 *              - 1435, 非法的融资融券负债类型 (OESERR_ILLEGAL_CREDIT_DEBT_TYPE)
 *              - 1436, 非法的融资融券归还模式 (OESERR_ILLEGAL_CREDIT_REPAY_MODE)
 *              - 1437, 非法的担保证券划转指令类型 (OESERR_ILLEGAL_COLLATERAL_TRANSFER_TYPE)
 *              - 1438, 无可归还的负债 (OESERR_NO_DEBT)
 *              - 1439, 不能归还当日开仓的合约 (OESERR_REPAY_INTRADY_NOT_ALLOW)
 *              - 1440, 不能归还已了结的合约 (OESERR_REPAY_FINISHED_NOT_ALLOW)
 *              - 1441, 指定合约的负债证券非委托归还的证券 (OESERR_REPAY_WRONG_STOCK)
 *              - 1442, 还券数量超过融券合约待归还数量 (OESERR_REPAY_STOCK_ORD_QTY_RANGE)
 *              - 1443, 未找到融资融券合约信息 (OESERR_CRD_DEBT_CONTRACT_NOT_FOUND)
 *              - 1444, 未通过维保比检查 (OESERR_MAINTENANCE_RATIO)
 *              - 1445, 申报价格不得低于最近成交价 (OESERR_BELOW_LAST_PRICE)
 *              - 1446, 信用合同不存在或者状态异常 (OESERR_CRD_COMPACT_ABNORMAL)
 *              - 1447, 信用客户处于监管黑名单 (OESERR_CRD_GUARD_BLOCKLIST)
 *              - 1448, 券商深圳市场融资融券专用交易单元未配置 (OESERR_BROKER_CRD_SZSE_PBU_NOT_CONFIG)
 *              - 15xx, 未通过集中度检查 (OESERR_CONCENTRATE_RATE)
 *
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
/** 1039, 非法的指令类型 */
#define OESERR_ILLEGAL_CMD_TYPE                 (&__ERRS_oesApiErrors[38])
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
/** 1231, 非法的业务类型 */
#define OESERR_ILLEGAL_BUSINESS_TYPE            (&__ERRS_oesApiErrors[60 + 30])
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
/** 1242, 非法的委托强制标志 */
#define OESERR_ILLEGAL_MANDATORY_FLAG           (&__ERRS_oesApiErrors[60 + 41])
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
/** 1250, 股东账户没有交易创业板核准制证券的权限 */
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
/** 1289, 股东账户没有交易可转换公司债券的权限 */
#define OESERR_NO_CONVERTIBLE_BOND_PERM         (&__ERRS_oesApiErrors[60 + 88])
/** 1290, 股东账户没有交易基础设施基金的权限 */
#define OESERR_NO_REITS_PERM                    (&__ERRS_oesApiErrors[60 + 89])
/** 1291, 限制入金 */
#define OESERR_DEPOSIT_LIMIT                    (&__ERRS_oesApiErrors[60 + 90])
/** 1292, 限制出金 */
#define OESERR_WITHDRAW_LIMIT                   (&__ERRS_oesApiErrors[60 + 91])
/* -------------------------           */


/*
 * 期权业务特有的错误号
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


/*
 * 两融业务特有的错误号
 */
/** 1401, 保证金可用余额不足 */
#define OESERR_MARGIN_NOT_ENOUGH                (&__ERRS_oesApiErrors[200 + 0])
/** 1402, 可用还款资金不足 */
#define OESERR_REPAY_CASH_NOT_ENOUGH            (&__ERRS_oesApiErrors[200 + 1])
/** 1403, 客户可用两融总额度不足 */
#define OESERR_CUST_CREDIT_TRADE_QUOTA          (&__ERRS_oesApiErrors[200 + 2])
/** 1404, 券商可用两融总额度不足 */
#define OESERR_BROKER_CREDIT_TRADE_QUOTA        (&__ERRS_oesApiErrors[200 + 3])
/** 1405, 客户可用融资额度不足 */
#define OESERR_CUST_MARGIN_BUY_QUOTA            (&__ERRS_oesApiErrors[200 + 4])
/** 1406, 券商可用融资额度不足 */
#define OESERR_BROKER_MARGIN_BUY_QUOTA          (&__ERRS_oesApiErrors[200 + 5])
/** 1407, 客户可用融券额度不足 */
#define OESERR_CUST_SHORT_SELL_QUOTA            (&__ERRS_oesApiErrors[200 + 6])
/** 1408, 券商可用融券额度不足 */
#define OESERR_BROKER_SHORT_SELL_QUOTA          (&__ERRS_oesApiErrors[200 + 7])
/** 1409, 可用融资头寸不足 */
#define OESERR_CASH_POSITION_NOT_ENOUGH         (&__ERRS_oesApiErrors[200 + 8])
/** 1410, 可用融券头寸不足 */
#define OESERR_SECURITY_POSITION_NOT_ENOUGH     (&__ERRS_oesApiErrors[200 + 9])
/** 1411, 无可用融资头寸 */
#define OESERR_CASH_GROUP_NOT_FOUND             (&__ERRS_oesApiErrors[200 + 10])
/** 1412, 无可用融券头寸 */
#define OESERR_NO_SECURITY_POSITION             (&__ERRS_oesApiErrors[200 + 11])
/** 1413, 非法的头寸性质 */
#define OESERR_ILLEGAL_CASH_GROUP_PROPERTY      (&__ERRS_oesApiErrors[200 + 12])
/** 1414, 单笔委托融资金额超上限 */
#define OESERR_ORD_MARGIN_BUY_CEILING           (&__ERRS_oesApiErrors[200 + 13])
/** 1415, 单笔委托融券规模超上限 */
#define OESERR_ORD_SHORT_SELL_CEILING           (&__ERRS_oesApiErrors[200 + 14])
/** 1416, 禁止担保品转入 */
#define OESERR_COLLATERAL_TRANSFER_IN_LIMIT     (&__ERRS_oesApiErrors[200 + 15])
/** 1417, 禁止担保品转出 */
#define OESERR_COLLATERAL_TRANSFER_OUT_LIMIT    (&__ERRS_oesApiErrors[200 + 16])
/** 1418, 禁止融资买入 */
#define OESERR_MARGIN_BUY_LIMIT                 (&__ERRS_oesApiErrors[200 + 17])
/** 1419, 禁止卖券还款 */
#define OESERR_REPAY_MARGIN_BY_SELL_LIMIT       (&__ERRS_oesApiErrors[200 + 18])
/** 1420, 禁止直接还款 */
#define OESERR_REPAY_MARGIN_DIRECT_LIMIT        (&__ERRS_oesApiErrors[200 + 19])
/** 1421, 禁止融券卖出 */
#define OESERR_SHORT_SELL_LIMIT                 (&__ERRS_oesApiErrors[200 + 20])
/** 1422, 禁止买券还券 */
#define OESERR_REPAY_STOCK_BY_BUY_LIMIT         (&__ERRS_oesApiErrors[200 + 21])
/** 1423, 禁止直接还券 */
#define OESERR_REPAY_STOCK_DIRECT_LIMIT         (&__ERRS_oesApiErrors[200 + 22])
/** 1424, 禁止董监高或大股东的融资融券交易 */
#define OESERR_CHIEF_OR_MAJOR_CREDIT_LIMIT      (&__ERRS_oesApiErrors[200 + 23])
/** 1425, 禁止提交限售股份为担保物 */
#define OESERR_RESTRICTED_STOCKS_TO_COLLATERAL  (&__ERRS_oesApiErrors[200 + 24])
/** 1426, 禁止个人投资者提交解除限售存量股份为担保物 */
#define OESERR_INDIVIDUAL_RESTRICTED_STOCKS_LIFTED_TO_COLLATERAL \
                                                (&__ERRS_oesApiErrors[200 + 25])
/** 1427, 禁止大小非开展该证券的融资融券交易 */
#define OESERR_NON_TRADABLE_SHARE_CREDIT_LIMIT  (&__ERRS_oesApiErrors[200 + 26])
/** 1428, 禁止其他股东角色开展该证券的融资融券交易 */
#define OESERR_OTHER_ROLES_CREDIT_LIMIT         (&__ERRS_oesApiErrors[200 + 27])
/** 1429, 无效的担保品状态 */
#define OESERR_ILLEGAL_COLLATERAL_STATUS        (&__ERRS_oesApiErrors[200 + 28])
/** 1430, 非担保证券 */
#define OESERR_NOT_COLLATERAL                   (&__ERRS_oesApiErrors[200 + 29])
/** 1431, 非融资标的证券 */
#define OESERR_NOT_MARGIN_BUY_UNDERLYING        (&__ERRS_oesApiErrors[200 + 30])
/** 1432, 非融券标的证券 */
#define OESERR_NOT_SHORT_SELL_UNDERLYING        (&__ERRS_oesApiErrors[200 + 31])
/** 1433, 非融资负债 */
#define OESERR_NOT_MARGIN_BUY_DEBT              (&__ERRS_oesApiErrors[200 + 32])
/** 1434, 非融券负债 */
#define OESERR_NOT_SHORT_SELL_DEBT              (&__ERRS_oesApiErrors[200 + 33])
/** 1435, 非法的融资融券负债类型 */
#define OESERR_ILLEGAL_CREDIT_DEBT_TYPE         (&__ERRS_oesApiErrors[200 + 34])
/** 1436, 非法的融资融券归还模式 */
#define OESERR_ILLEGAL_CREDIT_REPAY_MODE        (&__ERRS_oesApiErrors[200 + 35])
/** 1437, 非法的担保证券划转指令类型 */
#define OESERR_ILLEGAL_COLLATERAL_TRANSFER_TYPE (&__ERRS_oesApiErrors[200 + 36])
/** 1438, 无可归还的负债 */
#define OESERR_NO_DEBT                          (&__ERRS_oesApiErrors[200 + 37])
/** 1439, 不能归还当日开仓的合约 */
#define OESERR_REPAY_INTRADY_NOT_ALLOW          (&__ERRS_oesApiErrors[200 + 38])
/** 1440, 不能归还已了结的合约 */
#define OESERR_REPAY_FINISHED_NOT_ALLOW         (&__ERRS_oesApiErrors[200 + 39])
/** 1441, 指定合约的负债证券非委托归还的证券 */
#define OESERR_REPAY_WRONG_STOCK                (&__ERRS_oesApiErrors[200 + 40])
/** 1442, 还券数量超过融券合约待归还数量 */
#define OESERR_REPAY_STOCK_ORD_QTY_RANGE        (&__ERRS_oesApiErrors[200 + 41])
/** 1443, 未找到融资融券合约信息 */
#define OESERR_CRD_DEBT_CONTRACT_NOT_FOUND      (&__ERRS_oesApiErrors[200 + 42])
/** 1444, 未通过维持担保比检查 */
#define OESERR_MAINTENANCE_RATIO                (&__ERRS_oesApiErrors[200 + 43])
/** 1445, 申报价格不得低于最近成交价 */
#define OESERR_BELOW_LAST_PRICE                 (&__ERRS_oesApiErrors[200 + 44])
/** 1446, 信用合同不存在或者状态异常 */
#define OESERR_CRD_COMPACT_ABNORMAL             (&__ERRS_oesApiErrors[200 + 45])
/** 1447, 信用客户处于监管黑名单 */
#define OESERR_CRD_GUARD_BLOCKLIST              (&__ERRS_oesApiErrors[200 + 46])
/** 1448, 券商深圳市场融资融券专用交易单元未配置 */
#define OESERR_BROKER_CRD_SZSE_PBU_NOT_CONFIG   (&__ERRS_oesApiErrors[200 + 47])
/* -------------------------           */


/*
 * 两融业务集中度检查相关的错误号
 */
/** 1500, 未通过集中度检查 */
#define OESERR_CONCENTRATE_RATE                 (&__ERRS_oesApiErrors[260 + 0])
/** 1501, 客户单一证券持仓集中度超限 */
#define OESERR_CONCENTRATE_RATE_SECURITY_HOLDING                                \
                                                (&__ERRS_oesApiErrors[260 + 1])
/** 1502, 客户板块持仓集中度超限 */
#define OESERR_CONCENTRATE_RATE_SECTOR_HOLDING  (&__ERRS_oesApiErrors[260 + 2])
/** 1503, 客户单一证券融券集中度超限 */
#define OESERR_CONCENTRATE_RATE_SECURITY_SHORT_SELL                             \
                                                (&__ERRS_oesApiErrors[260 + 3])
/** 1504, 客户板块融券集中度 */
#define OESERR_CONCENTRATE_RATE_SECTOR_SHORT_SELL                               \
                                                (&__ERRS_oesApiErrors[260 + 4])

/** 1505, 客户单一证券持仓规模占当前证券流通市值的比例超限 */
#define OESERR_CONCENTRATE_CIRCULATION_MARKET_CAP_SECURITY_HOLDING              \
                                                (&__ERRS_oesApiErrors[260 + 5])
/** 1506, 所有客户单一证券持仓规模占当前证券流通市值的比例超限 */
#define OESERR_CONCENTRATE_CIRCULATION_MARKET_CAP_SECURITY_HOLDING_BROKER       \
                                                (&__ERRS_oesApiErrors[260 + 6])
/** 1507, 客户单一证券融资规模占当前证券流通市值的比例超限 */
#define OESERR_CONCENTRATE_CIRCULATION_MARKET_CAP_SECURITY_MARGIN_BUY           \
                                                (&__ERRS_oesApiErrors[260 + 7])
/** 1508, 所有客户单一证券融资规模占当前证券流通市值的比例超限 */
#define OESERR_CONCENTRATE_CIRCULATION_MARKET_CAP_SECURITY_MARGIN_BUY_BROKER    \
                                                (&__ERRS_oesApiErrors[260 + 8])
/** 1509, 客户单一证券融券规模占当前证券流通市值的比例超限 */
#define OESERR_CONCENTRATE_CIRCULATION_MARKET_CAP_SECURITY_SHORT_SELL           \
                                                (&__ERRS_oesApiErrors[260 + 9])
/** 1510, 所有客户单一证券融券规模占当前证券流通市值的比例超限 */
#define OESERR_CONCENTRATE_CIRCULATION_MARKET_CAP_SECURITY_SHORT_SELL_BROKER    \
                                                (&__ERRS_oesApiErrors[260 + 10])

/** 1511, 客户单一证券持仓规模占当前证券总市值的比例超限 */
#define OESERR_CONCENTRATE_TOTAL_MARKET_CAP_SECURITY_HOLDING                    \
                                                (&__ERRS_oesApiErrors[260 + 11])
/** 1512, 所有客户单一证券持仓规模占当前证券总市值的比例超限 */
#define OESERR_CONCENTRATE_TOTAL_MARKET_CAP_SECURITY_HOLDING_BROKER             \
                                                (&__ERRS_oesApiErrors[260 + 12])
/** 1513, 客户单一证券融资规模占当前证券总市值的比例超限 */
#define OESERR_CONCENTRATE_TOTAL_MARKET_CAP_SECURITY_MARGIN_BUY                 \
                                                (&__ERRS_oesApiErrors[260 + 13])
/** 1514, 所有客户单一证券融资规模占当前证券总市值的比例超限 */
#define OESERR_CONCENTRATE_TOTAL_MARKET_CAP_SECURITY_MARGIN_BUY_BROKER          \
                                                (&__ERRS_oesApiErrors[260 + 14])
/** 1515, 客户单一证券融券规模占当前证券总市值的比例超限 */
#define OESERR_CONCENTRATE_TOTAL_MARKET_CAP_SECURITY_SHORT_SELL                 \
                                                (&__ERRS_oesApiErrors[260 + 15])
/** 1516, 所有客户单一证券融券规模占当前证券总市值的比例超限 */
#define OESERR_CONCENTRATE_TOTAL_MARKET_CAP_SECURITY_SHORT_SELL_BROKER          \
                                                (&__ERRS_oesApiErrors[260 + 16])

/** 1517, 客户单一证券持仓规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECURITY_HOLDING                 \
                                                (&__ERRS_oesApiErrors[260 + 17])
/** 1518, 所有客户单一证券持仓规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECURITY_HOLDING_BROKER          \
                                                (&__ERRS_oesApiErrors[260 + 18])
/** 1519, 客户单一证券融资规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECURITY_MARGIN_BUY              \
                                                (&__ERRS_oesApiErrors[260 + 19])
/** 1520, 所有客户单一证券融资规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECURITY_MARGIN_BUY_BROKER       \
                                                (&__ERRS_oesApiErrors[260 + 20])
/** 1521, 客户单一证券融券规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECURITY_SHORT_SELL              \
                                                (&__ERRS_oesApiErrors[260 + 21])
/** 1522, 所有客户单一证券融券规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECURITY_SHORT_SELL_BROKER       \
                                                (&__ERRS_oesApiErrors[260 + 22])

/** 1523, 客户单一证券持仓规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECURITY_HOLDING                       \
                                                (&__ERRS_oesApiErrors[260 + 23])
/** 1524, 所有客户单一证券持仓规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECURITY_HOLDING_BROKER                \
                                                (&__ERRS_oesApiErrors[260 + 24])
/** 1525, 客户单一证券融资规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECURITY_MARGIN_BUY                    \
                                                (&__ERRS_oesApiErrors[260 + 25])
/** 1526, 所有客户单一证券融资规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECURITY_MARGIN_BUY_BROKER             \
                                                (&__ERRS_oesApiErrors[260 + 26])
/** 1527, 客户单一证券融券规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECURITY_SHORT_SELL                    \
                                                (&__ERRS_oesApiErrors[260 + 27])
/** 1528, 所有客户单一证券融券规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECURITY_SHORT_SELL_BROKER             \
                                                (&__ERRS_oesApiErrors[260 + 28])

/** 1529, 客户板块持仓规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECTOR_HOLDING                   \
                                                (&__ERRS_oesApiErrors[260 + 29])
/** 1530, 所有客户板块持仓规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECTOR_HOLDING_BROKER            \
                                                (&__ERRS_oesApiErrors[260 + 30])
/** 1531, 客户板块融资规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECTOR_MARGIN_BUY                \
                                                (&__ERRS_oesApiErrors[260 + 31])
/** 1532, 所有客户板块融资规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECTOR_MARGIN_BUY_BROKER         \
                                                (&__ERRS_oesApiErrors[260 + 32])
/** 1533, 客户板块融券规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECTOR_SHORT_SELL                \
                                                (&__ERRS_oesApiErrors[260 + 33])
/** 1534, 所有客户板块融券规模占公司净资本的比例超限 */
#define OESERR_CONCENTRATE_COMPANY_NET_CAPITAL_SECTOR_SHORT_SELL_BROKER         \
                                                (&__ERRS_oesApiErrors[260 + 34])

/** 1535, 客户板块持仓规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECTOR_HOLDING                         \
                                                (&__ERRS_oesApiErrors[260 + 35])
/** 1536, 所有客户板块持仓规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECTOR_HOLDING_BROKER                  \
                                                (&__ERRS_oesApiErrors[260 + 36])
/** 1537, 客户板块融资规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECTOR_MARGIN_BUY                      \
                                                (&__ERRS_oesApiErrors[260 + 37])
/** 1538, 所有客户板块融资规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECTOR_MARGIN_BUY_BROKER               \
                                                (&__ERRS_oesApiErrors[260 + 38])
/** 1539, 客户板块融券规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECTOR_SHORT_SELL                      \
                                                (&__ERRS_oesApiErrors[260 + 39])
/** 1540, 所有客户板块融券规模超限 */
#define OESERR_CONCENTRATE_SCALE_CEILING_SECTOR_SHORT_SELL_BROKER               \
                                                (&__ERRS_oesApiErrors[260 + 40])
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_PROTOCOL_ERRORS_H */
