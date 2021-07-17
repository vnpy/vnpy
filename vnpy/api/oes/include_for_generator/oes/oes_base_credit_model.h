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
 * @file    oes_base_credit_model.h
 *
 * 订单执行系统的融资融券交易相关基础领域模型(数据结构)定义
 *
 * @version 0.17    2020/09/16
 * @since   0.17    2020/09/16
 */

#ifndef _OES_BASE_CREDIT_MODEL_H
#define _OES_BASE_CREDIT_MODEL_H


#include    <oes_global/oes_base_model.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 融资融券合同编号最大长度 */
#define OES_CREDIT_COMPACT_ID_MAX_LEN       (32)
/** 融资融券合约编号最大长度 */
#define OES_CREDIT_DEBT_ID_MAX_LEN          (32)

/** 融资融券保证金比例/可充抵保证金折算率单位 (万分比) */
#define OES_CREDIT_MARGIN_RATIO_UNIT        (10000)
/** 融资融券利率费率比例单位 (万分比) */
#define OES_CREDIT_INTEREST_RATIO_UNIT      (10000)
/** 融资融券维持担保比例/集中度比例单位 (千分比) */
#define OES_CREDIT_MAINTENANCE_RATIO_UNIT   (1000)
/** 融资融券业务计息天数 */
#define OES_CREDIT_INTEREST_CALC_DAYS       (360)

/** 融资融券业务维持担保比例最大值 */
#define OES_CREDIT_MAINTENANCE_MAX_RATIO    (99999999)
/* -------------------------           */


/* ===================================================================
 * 枚举类型定义
 * =================================================================== */

/**
 * 融资融券负债类型
 */
typedef enum _eOesCrdDebtType {
    OES_CRD_DEBT_TYPE_UNDEFINE              = 0,        /**< 未定义的负债类型 */
    OES_CRD_DEBT_TYPE_MARGIN_BUY            = 1,        /**< 融资负债 */
    OES_CRD_DEBT_TYPE_SHORT_SELL            = 2,        /**< 融券负债 */
    OES_CRD_DEBT_TYPE_OTHER_DEBT            = 3,        /**< 其它负债 */
    __OES_CRD_DEBT_TYPE_MAX
} eOesCrdDebtTypeT;


/**
 * 头寸性质
 */
typedef enum _eOesCrdCashGroupProperty {
    OES_CRD_CASH_GROUP_PROP_UNDEFINE        = 0,        /**< 未定义的头寸性质 */
    OES_CRD_CASH_GROUP_PROP_PUBLIC          = 1,        /**< 公共头寸 */
    OES_CRD_CASH_GROUP_PROP_SPECIAL         = 2,        /**< 专项头寸 */
    __OES_CRD_CASH_GROUP_PROP_MAX
} eOesCrdCashGroupPropertyT;


/**
 * 融资融券负债状态
 */
typedef enum _eOesCrdDebtStatus {
    OES_CRD_DEBT_STATUS_UNDEFINE            = 0,        /**< 未定义的负债状态 */
    OES_CRD_DEBT_STATUS_NOT_TRADE           = 1,        /**< 合约尚未成交 */
    OES_CRD_DEBT_STATUS_NOT_REPAID          = 2,        /**< 未归还 */
    OES_CRD_DEBT_STATUS_PARTIALLY_REPAID    = 3,        /**< 部分归还 */
    OES_CRD_DEBT_STATUS_EXPIRED             = 4,        /**< 到期未了结 */

    OES_CRD_DEBT_STATUS_REPAID              = 5,        /**< 客户自行了结 */
    OES_CRD_DEBT_STATUS_MANNUAL_REPAID      = 6,        /**< 手工了结 */
    OES_CRD_DEBT_STATUS_NOT_DEBT            = 7,        /**< 未形成负债 */
    __OES_CRD_DEBT_STATUS_MAX
} eOesCrdDebtStatusT;


/**
 * 融资融券负债展期状态
 */
typedef enum _eOesCrdDebtPostponeStatus {
    OES_CRD_DEBT_POSTPONE_STATUS_UNDEFINE   = 0,        /**< 未定义的展期状态 */
    OES_CRD_DEBT_POSTPONE_STATUS_APPLICABLE = 1,        /**< 可申请 */
    OES_CRD_DEBT_POSTPONE_STATUS_APPLIED    = 2,        /**< 已申请 */
    OES_CRD_DEBT_POSTPONE_STATUS_APPROVED   = 3,        /**< 审批通过 */
    OES_CRD_DEBT_POSTPONE_STATUS_UNAPPROVED = 4,        /**< 审批不通过 */
    OES_CRD_DEBT_POSTPONE_STATUS_UNAPPLICABLE
                                            = 5,        /**< 不可申请 */
    __OES_CRD_DEBT_POSTPONE_STATUS_MAX
} eOesCrdDebtPostponeStatusT;


/**
 * 融资融券合同约定的负债归还模式
 */
typedef enum _eOesCrdDebtRepayMode {
    OES_CRD_DEBT_REPAY_MODE_UNDEFINE        = 0,        /**< 未定义的负债归还模式 */
    OES_CRD_DEBT_REPAY_MODE_MATCHING_PRINCIPAL
                                            = 1,        /**< 按比例归还 (利随本清) */
    OES_CRD_DEBT_REPAY_MODE_INTEREST_FIRST  = 2,        /**< 优先归还息费 (先息后本) */
    OES_CRD_DEBT_REPAY_MODE_PRINCIPAL_FIRST = 3,        /**< 优先归还本金 (先本后息) */
    __OES_CRD_DEBT_REPAY_MODE_MAX_COMPACT,              /**< 融资融券合同约定的负债归还模式的最大值 */

    __OES_CRD_DEBT_REPAY_MODE_INTEREST_ONLY = 10,       /**< 仅归还息费 (仅适用于API接口 @see OES_CRD_ASSIGNABLE_REPAY_MODE_INTEREST_ONLY) */
    __OES_CRD_DEBT_REPAY_MODE_MAX
} eOesCrdDebtRepayModeT;


/**
 * 可以由API接口指定的融资融券负债归还模式
 */
typedef enum _eOesCrdAssignableRepayMode {
    OES_CRD_ASSIGNABLE_REPAY_MODE_DEFAULT   = 0,        /**< 默认的负债归还模式 (使用融资融券合同约定的负债归还模式) */
    OES_CRD_ASSIGNABLE_REPAY_MODE_INTEREST_ONLY
                                            = 10,       /**< 仅归还息费 */
    __OES_CRD_ASSIGNABLE_REPAY_MODE_MAX
} eOesCrdAssignableRepayModeT;


/**
 * 融资融券负债流水类型
 */
typedef enum _eOesCrdDebtJournalType {
    OES_CRD_DEBT_JOURNAL_TYPE_OPEN_POSITION = 0,        /**< 合约开仓 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_MARGIN_BY_SELL
                                            = 1,        /**< 卖券还款 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_MARGIN_DIRECT
                                            = 2,        /**< 直接还款 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_STOCK_BY_BUY
                                            = 3,        /**< 买券还券 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_STOCK_DIRECT
                                            = 4,        /**< 直接还券 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_STOCK_BY_CASH
                                            = 5,        /**< 现金了结融券负债 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_STOCK_BY_OUTSIDE
                                            = 6,        /**< 场外了结融券负债 */
    OES_CRD_DEBT_JOURNAL_TYPE_REPAY_MARGIN_BY_OUTSIDE
                                            = 7,        /**< 场外了结融资负债 */
    OES_CRD_DEBT_JOURNAL_TYPE_CONTRACT_POST_PONE
                                            = 8,        /**< 合约展期(审批) */
    OES_CRD_DEBT_JOURNAL_TYPE_OTHER         = 9,        /**< 其它类型 */
    __OES_CRD_DEBT_JOURNAL_TYPE_MAX
} eOesCrdDebtJournalTypeT;


/**
 * 信用客户警戒状态
 */
typedef enum _eOesCrdCustGuardStatus {
    OES_CRD_CUST_GUARD_STATUS_NORMAL        = 0,        /**< 正常 */
    OES_CRD_CUST_GUARD_STATUS_ALERT         = 1,        /**< 警惕 */
    OES_CRD_CUST_GUARD_STATUS_BLOCKLIST     = 2,        /**< 黑名单 */
    __OES_CRD_CUST_GUARD_STATUS_MAX
} eOesCrdCustGuardStatusT;
/* -------------------------           */


/* ===================================================================
 * 融资融券资金头寸(可融资头寸)基础信息定义
 * =================================================================== */

/**
 * 融资融券资金头寸(可融资头寸)的基础信息内容定义
 */
#define __OES_CRD_CASH_POSITION_BASE_INFO_PKT                           \
        /** 资金账户代码 */ \
        char            cashAcctId[OES_CASH_ACCT_ID_MAX_LEN]; \
        /** 头寸编号 */ \
        int32           cashGroupNo; \
        /** 头寸性质 @see eOesCrdCashGroupPropertyT */ \
        uint8           cashGroupProperty; \
        /** 币种 @see eOesCurrTypeT */ \
        uint8           currType; \
        /** 按64位对齐的填充域 */ \
        uint8           __CRD_CASH_POSITION_BASE_filler[2]; \
        \
        /** 资金头寸金额 (含已用) */ \
        int64           positionAmt; \
        /** 日间已归还金额 */ \
        int64           repaidPositionAmt; \
        /** 累计已用金额 (含日初已用) */ \
        int64           usedPositionAmt; \
        /** 当前尚未成交的在途冻结金额 */ \
        int64           frzPositionAmt; \
        \
        /** 期初余额, 单位精确到元后四位, 即1元 = 10000 */ \
        int64           originalBalance; \
        /** 期初可用余额, 单位精确到元后四位, 即1元 = 10000 */ \
        int64           originalAvailable; \
        /** 期初已用金额 (期初待归还负债金额) */ \
        int64           originalUsed; \
        \
        /** 预留的备用字段 */ \
        char            __CRD_CASH_POSITION_BASE_reserve[32]


/* 结构体的初始化值定义 */
#define __NULLOBJ_OES_CRD_CASH_POSITION_BASE_INFO_PKT                   \
        {0}, 0, 0, 0, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 融资融券资金头寸的基础信息结构体定义
 */
typedef struct _OesCrdCashPositionBaseInfo {
    __OES_CRD_CASH_POSITION_BASE_INFO_PKT;
} OesCrdCashPositionBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CASH_POSITION_BASE_INFO                         \
        __NULLOBJ_OES_CRD_CASH_POSITION_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 融资融券证券头寸(可融券头寸)基础信息定义
 * =================================================================== */

/**
 * 融资融券证券头寸(可融券头寸)的基础信息内容定义
 */
#define __OES_CRD_SECURITY_POSITION_BASE_INFO_PKT                       \
        /** 证券账户 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 证券代码 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市场代码 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 头寸性质 @see eOesCrdCashGroupPropertyT */ \
        uint8           cashGroupProperty; \
        /** 按64位对齐的填充域 */ \
        uint8           __SECURITY_POSITION_BASE_filler[2]; \
        /** 头寸编号 */ \
        int32           cashGroupNo; \
        \
        /** 证券头寸数量 (含已用) */ \
        int64           positionQty; \
        /** 日间已归还数量 (当日归还不可用) */ \
        int64           repaidPositionQty; \
        /** 累计已用数量 (含日初已用) */ \
        int64           usedPositionQty; \
        /** 当前尚未成交的在途冻结数量 */ \
        int64           frzPositionQty; \
        \
        /** 期初数量 */ \
        int64           originalBalanceQty; \
        /** 期初可用数量 */ \
        int64           originalAvailableQty; \
        /** 期初已用数量 (期初待归还负债数量) */ \
        int64           originalUsedQty; \
        \
        /** 预留的备用字段 */ \
        char            __SECURITY_POSITION_BASE_reserve[32]


/* 结构体的初始化值定义 */
#define __NULLOBJ_OES_CRD_SECURITY_POSITION_BASE_INFO_PKT               \
        {0}, {0}, 0, 0, {0}, 0, \
        0, 0, 0, 0, \
        0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 融资融券证券头寸的基础信息结构体定义
 */
typedef struct _OesCrdSecurityPositionBaseInfo {
    __OES_CRD_SECURITY_POSITION_BASE_INFO_PKT;
} OesCrdSecurityPositionBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_SECURITY_POSITION_BASE_INFO                     \
        __NULLOBJ_OES_CRD_SECURITY_POSITION_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 融资融券合约(负债)基础信息定义
 * =================================================================== */

/**
 * 融资融券合约的基础信息内容定义
 */
#define __OES_CRD_DEBT_CONTRACT_BASE_INFO_PKT                           \
        /** 合约编号 */ \
        char            debtId[OES_CREDIT_DEBT_ID_MAX_LEN]; \
        /** 股东账户代码 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 证券代码 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        \
        /** 市场代码 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 证券类型 @see eOesSecurityTypeT */ \
        uint8           securityType; \
        /** 证券子类型 @see eOesSubSecurityTypeT */ \
        uint8           subSecurityType; \
        /** 证券的产品类型 @see eOesProductTypeT */ \
        uint8           securityProductType; \
        \
        /** 负债类型 @see eOesCrdDebtTypeT */ \
        uint8           debtType; \
        /** 负债状态 @see eOesCrdDebtStatusT */ \
        uint8           debtStatus; \
        /** 期初负债状态 @see eOesCrdDebtStatusT */ \
        uint8           originalDebtStatus; \
        /** 负债归还模式 @see eOesCrdDebtRepayModeT */ \
        uint8           debtRepayMode; \
        \
        /** 委托日期 (格式为 YYYYMMDD, 形如 20160830) */ \
        int32           ordDate; \
        /** 委托价格 (单位精确到元后四位, 即1元 = 10000) */ \
        int32           ordPrice; \
        /** 委托数量 */ \
        int32           ordQty; \
        /** 成交数量 */ \
        int32           trdQty; \
        \
        /** 委托金额 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           ordAmt; \
        /** 成交金额 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           trdAmt; \
        /** 成交费用 (仅用于展示, 负债部分参见合约手续费(debtFee)字段. 单位精确到元后四位, 即1元 = 10000) */ \
        int64           trdFee; \
        \
        /** 实时合约金额 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           currentDebtAmt; \
        /** 实时合约手续费 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           currentDebtFee; \
        /** 实时合约利息 (含罚息. 单位精确到元后四位, 即1元 = 10000) */ \
        int64           currentDebtInterest; \
        /** 实时合约数量 */ \
        int32           currentDebtQty; \
        \
        /** 在途冻结数量 */ \
        int32           uncomeDebtQty; \
        /** 在途冻结金额 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           uncomeDebtAmt; \
        /** 在途冻结手续费 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           uncomeDebtFee; \
        /** 在途冻结利息 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           uncomeDebtInterest; \
        \
        /**
         * 累计已归还金额 (单位精确到元后四位, 即1元 = 10000)
         * - 对于融资，是归还的融资负债金额
         * - 对于融券，是归还的融券数量*归还时的成交价格 (即实际归还金额)
         */ \
        int64           totalRepaidAmt; \
        /** 累计已归还手续费 (仅包含当日归还. 单位精确到元后四位, 即1元 = 10000) */ \
        int64           totalRepaidFee; \
        /** 累计已归还利息 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           totalRepaidInterest; \
        /**
         * 累计已归还数量
         * - 对于融券，是归还的融券负债数量
         * - 对于融资，是归还的融资金额/归还时该证券最新价格
         */ \
        int32           totalRepaidQty; \
        /** 按64位对齐填充域 */ \
        int32           __CRD_DEBT_CONTRACT_BASE_filler2; \
        \
        /** 期初待归还金额 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           originalDebtAmt; \
        /** 期初待归还手续费 (单位精确到元后四位, 即1元 = 10000) */ \
        int64           originalDebtFee; \
        /** 期初待归还利息 (含罚息. 单位精确到元后四位, 即1元 = 10000) */ \
        int64           originalDebtInterest; \
        /** 期初待归还数量 */ \
        int32           originalDebtQty; \
        \
        /**
         * 期初已归还数量
         * - 对于融券，是归还的融券负债数量
         * - 对于融资，是归还的融资金额/归还时该证券最新价格
         */ \
        int32           originalRepaidQty; \
        /**
         * 期初已归还金额 (单位精确到元后四位, 即1元 = 10000)
         * - 对于融资，是归还的融资负债金额
         * - 对于融券，是归还的融券数量*归还时成交价格
         */ \
        int64           originalRepaidAmt; \
        /** 期初已归还利息 (含罚息. 单位精确到元后四位, 即1元 = 10000) */ \
        int64           originalRepaidInterest; \
        \
        /** 罚息 (仅供展示, 已在利息中体现. 单位精确到元后四位, 即1元 = 10000) */ \
        int64           punishInterest; \
        \
        /** 保证金比例 (单位:万分比) */ \
        int32           marginRatio; \
        /** 融资利率/融券费率 (单位精确到万分之一, 即费率8.36% = 836) */ \
        int32           interestRate; \
        /** 负债截止日期 (格式为 YYYYMMDD, 形如 20160830) */ \
        int32           repayEndDate; \
        /** 头寸编号 */ \
        int32           cashGroupNo; \
        /** 展期次数 */ \
        int32           postponeTimes; \
        /** 展期状态 @see eOesCrdDebtPostponeStatusT */ \
        uint8           postponeStatus; \
        /** 按64位对齐填充域 */ \
        uint8           __CRD_DEBT_CONTRACT_BASE_filler3[3]; \
        \
        /** 预留的备用字段 */ \
        char            __CREDIT_DEBT_BASE_reserve[32]


/* 结构体的初始化值定义 */
#define __NULLOBJ_OES_CRD_DEBT_CONTRACT_BASE_INFO_PKT                   \
        {0}, {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, \
        0, \
        0, 0, 0, 0, 0, 0, {0}, \
        {0}
/* -------------------------           */


/**
 * 融资融券合约的基础信息结构体定义
 */
typedef struct _OesCrdDebtContractBaseInfo {
    __OES_CRD_DEBT_CONTRACT_BASE_INFO_PKT;
} OesCrdDebtContractBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_DEBT_CONTRACT_BASE_INFO                         \
        __NULLOBJ_OES_CRD_DEBT_CONTRACT_BASE_INFO_PKT
/* -------------------------           */


/**
 * 融资融券合约回报信息结构体定义
 */
typedef struct _OesCrdDebtContractReport {
    __OES_CRD_DEBT_CONTRACT_BASE_INFO_PKT;

    /** 同标的证券所有融券合约的合计可归还数量 (可归还数量 = 实时合约数量 - 归还在途数量) */
    int64               securityRepayableQty;
    /** 该融券合约的当前可归还数量 (可归还数量 = 实时合约数量 - 归还在途数量) */
    int32               contractRepayableQty;
    /** 按64位对齐填充域 */
    int32               __fillter;

    /** 保留字段 */
    char                __reserve[64];
} OesCrdDebtContractReportT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_DEBT_CONTRACT_REPORT                            \
        __NULLOBJ_OES_CRD_DEBT_CONTRACT_BASE_INFO_PKT, \
        0, 0, 0, \
        {0}
/* -------------------------           */


/* ===================================================================
 * 融资融券合约流水信息定义
 * =================================================================== */

/**
 * 融资融券合约负债流水的基础信息内容定义
 * @note    记录合约负债变动流水, 包括: 开仓流水、归还流水、以及合约展期流水
 *          - 对于归还流水, 发生金额、发生费用、发生利息、发生证券数量为负数
 *          - 对于开仓流水, 对应数据为正数
 *          - 对于合约展期流水, 发生金额、发生费用等数据为0
 */
#define __OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT                            \
        /** 合约编号 */ \
        char            debtId[OES_CREDIT_DEBT_ID_MAX_LEN]; \
        /** 股东账户代码 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 证券代码 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        \
        /** 市场代码 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 负债类型 @see eOesCrdDebtTypeT */ \
        uint8           debtType; \
        /** 流水类型 @see eOesCrdDebtJournalTypeT */ \
        uint8           journalType; \
        /** 强制标志 @see eOesOrdMandatoryFlagT */ \
        uint8           mandatoryFlag; \
        /** 同一融资融券合约的负债流水的顺序号 */ \
        int32           seqNo; \
        \
        /** 发生金额 (不含息费) */ \
        int64           occurAmt; \
        /** 发生费用 */ \
        int64           occurFee; \
        /** 发生利息 */ \
        int64           occurInterest; \
        /** 发生证券数量 */ \
        int32           occurQty; \
        /** 后余证券数量 */ \
        int32           postQty; \
        /** 后余金额 (不含息费) */ \
        int64           postAmt; \
        /** 后余费用 */ \
        int64           postFee; \
        /** 后余利息 */ \
        int64           postInterest; \
        /** 归还息费时使用融券卖出所得抵扣的金额 */ \
        int64           useShortSellGainedAmt; \
        \
        /** 委托日期 (格式为 YYYYMMDD, 形如 20160830) */ \
        int32           ordDate; \
        /** 委托时间 (格式为 HHMMSSsss, 形如 141205000) */ \
        int32           ordTime; \
        /** 预留的备用字段 */ \
        char            __CRD_DEBT_JOURNAL_BASE_reserve[32]


/* 结构体的初始化值定义 */
#define __NULLOBJ_OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT                    \
        {0}, {0}, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0, {0}
/* -------------------------           */


/**
 * 融资融券合约负债流水的基础信息结构体定义
 */
typedef struct _OesCrdDebtJournalBaseInfo {
    __OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT;
} OesCrdDebtJournalBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_DEBT_JOURNAL_BASE_INFO                          \
        __NULLOBJ_OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT
/* -------------------------           */


/**
 * 融资融券合约流水变动信息回报结构体定义
 */
typedef struct _OesCrdDebtJournalReport {
    __OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT;
} OesCrdDebtJournalReportT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_DEBT_JOURNAL_REPORT                             \
        __NULLOBJ_OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 客户单证券融资融券负债统计基础信息定义
 * =================================================================== */

/**
 * 客户单证券融资融券负债统计基础信息的结构体定义
 */
typedef struct _OesCrdSecurityDebtStatsBaseInfo {
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 股东账户代码 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 市场代码 @see eOesMarketIdT */
    uint8               mktId;
    /** 按64位对齐的填充域 */
    uint8               __filler[7];

    /** 累计买入/持有持仓数量 (日初持仓数量+已成交数量) */
    int64               collateralTotalBuyQty;
    /** 在途买入数量 */
    int64               collateralUncomeBuyQty;
    /** 在途买入冻结的交易金额 (包含国债利息), 单位精确到元后四位, 即1元 = 10000 */
    int64               collateralUncomeBuyFrzAmt;
    /** 在途买入冻结的交易费用, 单位精确到元后四位, 即1元 = 10000 */
    int64               collateralUncomeBuyFrzFee;
    /** 在途转入数量 (包含已确认和未确认数量, 不包含已撤单数量) */
    int64               collateralUncomeTrsfInQty;

    /** 累计卖出持仓数量 (已成交数量) */
    int64               collateralTotalSellQty;
    /** 在途卖出数量 */
    int64               collateralUncomeSellQty;
    /** 累计转出数量 (包含已确认和未确认数量, 不包含已撤单数量) */
    int64               collateralTotalTrsfOutQty;
    /** 直接还券数量 (包含已确认和未确认数量, 不包含已撤单数量) */
    int64               collateralTotalRepayDirectQty;

    /**
     * 证券持仓市值 (不包含在途买入、在途卖出和在途转出; 单位精确到元后四位, 即1元=10000)
     * @note: 证券持仓总市值的计算可参考如下公式:
     *      - 证券持仓总市值 = 证券持仓市值 + 在途卖出证券持仓市值 + 在途转出证券持仓市值
     */
    int64               holdingMarketCap;
    /** 在途卖出证券持仓市值 (单位精确到元后四位, 即1元=10000) */
    int64               collateralUncomeSellMarketCap;
    /** 在途转出证券持仓市值 (单位精确到元后四位, 即1元=10000)  */
    int64               collateralTrsfOutMarketCap;
    /** 可充抵的保证金金额 (包含担保品在途买入和担保品在途卖出, 不包含转出; 单位精确到元后四位, 即1元=10000) */
    int64               collateralMargin;

    /** 融资负债 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtAmt;
    /** 融资负债交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtFee;
    /** 融资负债利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtInterest;
    /** 融资负债数量 */
    int64               marginBuyDebtQty;

    /** 在途融资金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyUncomeAmt;
    /** 在途融资交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyUncomeFee;
    /** 在途融资利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyUncomeInterest;
    /** 在途融资数量 */
    int64               marginBuyUncomeQty;

    /** 融资买入证券市值 */
    int64               marginBuyDebtMarketCap;
    /** 融资买入负债占用的保证金金额 (包含在途融资买入, 公式: (融资买入金额-已归还融资金额+在途融资金额)×融资买入保证金比例) */
    int64               marginBuyDebtUsedMargin;

    /** 融券卖出金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtAmt;
    /** 融券负债交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtFee;
    /** 融券负债利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtInterest;
    /** 融券负债数量 */
    int64               shortSellDebtQty;

    /** 在途融券卖出金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellUncomeAmt;
    /** 在途融券交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellUncomeFee;
    /** 在途融券利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellUncomeInterest;
    /** 在途融券数量 */
    int64               shortSellUncomeQty;

    /** 该证券所有融券合约的合计可归还数量 (可归还数量 = 历史融券合约负债数量 - 归还在途数量) */
    int64               securityRepayableQty;

    /** 融券卖出证券市值 */
    int64               shortSellDebtMarketCap;
    /** 融券卖出负债占用的保证金金额 (包含在途融券卖出, 公式: (融券卖出证券市值+在途融券卖出证券市值)×融券卖出保证金比例) */
    int64               shortSellDebtUsedMargin;

    /** 其他负债 (单位精确到元后四位, 即1元 = 10000) */
    int64               otherDebtAmt;
    /** 其他负债利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               otherDebtInterest;

    /** 证券名称 (UTF-8 编码) */
    char                securityName[OES_SECURITY_NAME_MAX_LEN];
    /** 保留字段 */
    char                __reserve[64];
} OesCrdSecurityDebtStatsBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_SECURITY_DEBT_STATS_BASE_INFO                   \
        {0}, {0}, {0}, 0, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, \
        0, 0, \
        0, 0, \
        {0}, {0}
/* -------------------------           */


/* ===================================================================
 * 信用资产基础信息定义
 * =================================================================== */

/**
 * 信用资产基础信息的结构体定义
 */
typedef struct _OesCrdCreditAssetBaseInfo {
    /** 资金账户代码 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 币种 @see eOesCurrTypeT */
    uint8               currType;
    /** 资金帐户类别(冗余自资金账户) @see eOesAcctTypeT */
    uint8               cashType;
    /** 资金帐户状态(冗余自资金账户) @see eOesAcctStatusT */
    uint8               cashAcctStatus;
    /** 按64位对齐的填充域 */
    uint8               __filler;
    /** 维持担保比例 (千分比) */
    int32               maintenaceRatio;

    /**
     * 总资产 (包含其它担保资产价值, 单位精确到元后四位, 即1元=10000)
     * - 总资产=现金余额(包含冻结资金在内的资金余额)+担保证券市值(不包含买入在途,包含卖出在途和转出在途)+其它担保资产价值
     */
    int64               totalAssetValue;
    /** 其它担保资产价值 (单位精确到元后四位, 即1元 = 10000) */
    int64               otherBackedAssetValue;
    /**
     * 总负债 (不包括在途负债, 单位精确到元后四位, 即1元=10000)
     * - 总负债=融资已买入金额+融券已卖出证券市值+利息及费用(不包含未成交部分的利息及费用)+其它负债金额
     */
    int64               totalDebtValue;

    /**
     * 证券持仓市值 (不包含在途买入、在途卖出和在途转出; 单位精确到元后四位, 即1元=10000)
     * @note: 证券持仓总市值的计算可参考如下公式:
     * - 证券持仓总市值=证券持仓市值+在途卖出证券持仓市值+在途转出证券持仓市值
     */
    int64               holdingMarketCap;
    /** 在途卖出证券持仓市值 (单位精确到元后四位, 即1元=10000) */
    int64               collateralUncomeSellMarketCap;
    /** 在途转出证券持仓市值 (单位精确到元后四位, 即1元=10000)  */
    int64               collateralTrsfOutMarketCap;

    /** 现金余额 (包含融券卖出所得资金和冻结资金在内的资金余额; 单位精确到元后四位, 即1元=10000) */
    int64               cashBalance;
    /** 现金还款/买融资标的 可用余额 (单位精确到元后四位, 即1元 = 10000) */
    int64               availableBal;
    /** 可取余额 (单位精确到元后四位, 即1元 = 10000) */
    int64               drawableBal;
    /** 保证金可用余额 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginAvailableBal;

    /** 融资买入授信额度 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyMaxQuota;
    /** 融券卖出授信额度 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellMaxQuota;
    /** 融资融券总授信额度 (单位精确到元后四位, 即1元 = 10000) */
    int64               creditTotalMaxQuota;

    /** 融资可用额度 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyAvailableQuota;
    /** 融券可用额度 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellAvailableQuota;

    /** 融资负债 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtAmt;
    /** 融资负债交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtFee;
    /** 融资负债利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtInterest;

    /** 在途融资金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyUncomeAmt;
    /** 在途融资交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyUncomeFee;
    /** 在途融资利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyUncomeInterest;

    /** 融资买入证券市值 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtMarketCap;
    /** 融资买入负债占用的保证金金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               marginBuyDebtUsedMargin;

    /** 融券卖出金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtAmt;
    /** 融券负债交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtFee;
    /** 融券负债利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtInterest;

    /** 在途融券卖出金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellUncomeAmt;
    /** 在途融券交易费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellUncomeFee;
    /** 在途融券利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellUncomeInterest;

    /** 融券卖出证券市值 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtMarketCap;
    /** 融券卖出负债占用的保证金金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellDebtUsedMargin;

    /** 融券卖出所得总额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellGainedAmt;
    /** 融券卖出所得可用金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               shortSellGainedAvailableAmt;

    /** 其他负债 (单位精确到元后四位, 即1元 = 10000) */
    int64               otherDebtAmt;
    /** 其他负债利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               otherDebtInterest;

    /** 融资融券专项头寸总费用 (包含融资专项头寸成本费、融券专项头寸成本费和转融通成本费; 单位精确到元后四位, 即1元 = 10000) */
    int64               creditTotalSpecialFee;
    /** 融资专项头寸成本费, 单位精确到元后四位, 即1元 = 10000 */
    int64               marginBuySpecialFee;
    /** 融券专项头寸成本费, 单位精确到元后四位, 即1元 = 10000 */
    int64               shortSellSpecialFee;

    /** 保留字段 */
    char                __reserve[64];
} OesCrdCreditAssetBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CREDIT_ASSET_BASE_INFO                          \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, \
        0, 0, \
        0, 0, \
        0, 0, 0, \
        {0}
/* -------------------------           */


/* ===================================================================
 * 余券基础信息定义
 * =================================================================== */

/**
 * 余券基础信息的结构体定义
 */
typedef struct _OesCrdExcessStockBaseInfo {
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码  @see eOesMarketIdT */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 日初余券数量 */
    int64               originExcessStockQty;
    /** 余券数量 (日初余券数量 + 日中余券数量) */
    int64               excessStockTotalQty;
    /** 余券已划转数量 (包含已确认和未确认数量, 不包含已撤单数量) */
    int64               excessStockUncomeTrsfQty;
    /** 余券可划转数量 */
    int64               excessStockTrsfAbleQty;

    /** 保留字段 */
    char                __reserve[16];
} OesCrdExcessStockBaseInfoT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_EXCESS_STOCK_BASE_INFO                          \
        {0}, {0}, {0}, 0, {0}, \
        0, 0, 0, 0, \
        {0}
/* -------------------------           */


/* ===================================================================
 * 融资融券负债归还请求的结构体定义
 * =================================================================== */

/**
 * 融资融券负债归还请求 (除直接还款以外的直接还券、买券还券、卖券还款等负债归还请求)
 */
typedef struct _OesCrdRepayReq {
    /** 委托请求信息 */
    OesOrdReqT          ordReq;

    /** 归还模式 (仅适用于归还融资负债) @see eOesCrdAssignableRepayModeT */
    uint8               repayMode;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 指定归还的合约编号 */
    char                debtId[OES_CREDIT_DEBT_ID_MAX_LEN];
} OesCrdRepayReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_REPAY_REQ                                       \
        {NULLOBJ_OES_ORD_REQ}, \
        0, {0}, \
        {0}
/* -------------------------           */


/* ===================================================================
 * 直接还款请求的结构体定义
 * =================================================================== */

/**
 * 直接还款请求的基础内容定义
 */
#define __OES_CRD_CASH_REPAY_REQ_BASE_PKT                               \
        /** 客户委托流水号 (由客户端维护的递增流水) */ \
        int32           clSeqNo; \
        /** 归还模式 @see eOesCrdAssignableRepayModeT */ \
        uint8           repayMode; \
        /** 归还指令类型 @see eOesCrdDebtJournalTypeT */ \
        uint8           repayJournalType; \
        /** 按64位对齐填充域 */ \
        uint8           __CRD_CASH_REPAY_REQ_BASE_filler[2]; \
        /** 归还金额, 单位精确到元后四位, 即1元 = 10000 */ \
        int64           repayAmt; \
        \
        /** 资金账户代码 */ \
        char            cashAcctId[OES_CASH_ACCT_ID_MAX_LEN]; \
        /** 指定归还的合约编号 */ \
        char            debtId[OES_CREDIT_DEBT_ID_MAX_LEN]; \
        \
        /** 用户私有信息 (由客户端自定义填充, 并在回报数据中原样返回) */ \
        union { \
            uint64      u64;                /**< uint64 类型的用户私有信息 */ \
            int64       i64;                /**< int64 类型的用户私有信息 */ \
            uint32      u32[2];             /**< uint32[2] 类型的用户私有信息 */ \
            int32       i32[2];             /**< int32[2] 类型的用户私有信息 */ \
            char        c8[8];              /**< char[8] 类型的用户私有信息 */ \
        } userInfo


/* 结构体的初始化值定义 */
#define __NULLOBJ_OES_CRD_CASH_REPAY_REQ_BASE_PKT                       \
        0, 0, 0, {0}, 0, \
        {0}, {0}, \
        {0}
/* -------------------------           */


/**
 * 融资融券直接还款请求定义
 */
typedef struct _OesCrdCashRepayReq {
    __OES_CRD_CASH_REPAY_REQ_BASE_PKT
    __OES_ORD_REQ_LATENCY_FIELDS;
} OesCrdCashRepayReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CASH_REPAY_REQ                                  \
        __NULLOBJ_OES_CRD_CASH_REPAY_REQ_BASE_PKT \
        __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS
/* -------------------------           */


/**
 * 融资融券直接还款请求执行状态回报的结构体定义
 */
typedef struct _OesCrdCashRepayReport {
    __OES_CRD_CASH_REPAY_REQ_BASE_PKT
    __OES_ORD_REQ_LATENCY_FIELDS;

    /** 证券账户 (仅适用于管理端现金了结/场外了结融券负债委托回报) */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码 (仅适用于管理端现金了结/场外了结融券负债委托回报) */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 市场代码 @see eOesMarketIdT */
    uint8               mktId;
    /** 按64位对齐的填充域 */
    uint8               __filler1[7];
    /** 委托价格 (公允价格, 仅适用于管理端现金了结/场外了结融券负债委托回报. 单位精确到元后四位, 即1元 = 10000) */
    int32               ordPrice;
    /** 归还数量 (仅适用于管理端现金了结/场外了结融券负债委托回报) */
    int32               ordQty;

    /** 委托日期 (格式为 YYYYMMDD, 形如 20160830) */
    int32               ordDate;
    /** 委托时间 (格式为 HHMMSSsss, 形如 141205000) */
    int32               ordTime;

    /** 客户订单编号 (在OES内具有唯一性的内部委托编号, 只有有效的委托才会生成, 被拒绝的委托该字段为0) */
    int64               clOrdId;
    /** 客户端编号 */
    int16               clientId;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 委托强制标志 */
    uint8               mandatoryFlag;

    /** 订单当前状态 @see eOesOrdStatusT */
    uint8               ordStatus;
    /** 所有者类型 (被拒绝的委托该字段为0) @see eOesOwnerTypeT */
    uint8               ownerType;
    /** 按64位对齐的填充数据 */
    uint8               __filler2[2];
    /** 订单拒绝原因 */
    int32               ordRejReason;

    /** 实际归还数量 (仅适用于管理端现金了结/场外了结融券负债委托回报) */
    int32               repaidQty;
    /** 实际归还金额 (单位精确到元后四位, 即1元 = 10000) */
    int64               repaidAmt;
    /** 实际归还费用 (单位精确到元后四位, 即1元 = 10000) */
    int64               repaidFee;
    /** 实际归还利息 (单位精确到元后四位, 即1元 = 10000) */
    int64               repaidInterest;

    /** 营业部编号 (被拒绝的委托该字段为0) */
    int32               branchId;
    /** 按64位对齐的填充数据 */
    int32               __filler3;
} OesCrdCashRepayReportT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CASH_REPAY_REPORT                               \
        __NULLOBJ_OES_CRD_CASH_REPAY_REQ_BASE_PKT \
        __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS, \
        {0}, {0}, 0, {0}, 0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, {0}, 0, \
        0, 0, 0, 0, \
        0, 0
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_BASE_CREDIT_MODEL_H */
