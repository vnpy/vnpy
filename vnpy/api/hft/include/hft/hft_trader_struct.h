/**
 * @file    hft_trader_struct.h
 * @brief   交易业务数据和结构定义
 */

#ifndef _HFT_TRADER_STRUCT_H_
#define _HFT_TRADER_STRUCT_H_

#include "hft_trader_common.h"

namespace HFT {

// 市场类型名字，与行情保持一致
#define MARKET_SH "SH"          // 上海交易所
#define MARKET_SZ "SZ"          // 深圳交易所
#define MARKET_CFFEX "CFFEX"    // 中金所
#define MARKET_CZCE "CZCE"      // 郑商所
#define MARKET_DCE "DCE"        // 大商所
#define MARKET_SHFE "SHFE"      // 上期所
#define MARKET_HK "HK"          // 香港交易所
#define MARKET_SGE "SGE"        // 金交所
#define MARKET_CFETS "CFETS"    // 外汇交易中心
#define MARKET_SHOP "SHOP"      // 上海交易所期权
#define MARKET_SZOP "SZOP"      // 深圳交易所期权
#define MARKET_SZHK "SZHK"      // 深港通
#define MARKET_SHHK "SHHK"      // 沪港通

// 整形的市场类型
enum MarketType {
    Market_SSE = 1,         // 上海交易所
    Market_SZSE = 2,        // 深圳交易所
    Market_SSE_OP = 10,     // 上海交易所期权，为了与行情保持一致
    Market_SZSE_OP = 11,    // 深圳交易所期权，为了与行情保持一致
};

// 订单状态定义
enum OrderStatus {
    OrderStatus_PendingNew = 1,         // 订单待报
    OrderStatus_New = 2,                // 订单已报
    OrderStatus_PartiallyFilled = 3,    // 订单部分成交
    OrderStatus_Filled = 4,             // 订单全部成交
    OrderStatus_PendingCancel = 5,      // 撤单待报
    OrderStatus_Canceling = 6,          // 已报待撤
    OrderStatus_CancelFilled = 7,       // 订单已撤销
    OrderStatus_PartiallyCanceled = 8,  // 部成部撤
    OrderStatus_Rejected = 9,           // 订单已拒绝
    OrderStatus_CancelRejected = 10,    // 撤单废单
};

// 订单类型定义
enum OrderType {
    OrderType_LMT = 1,   // 限价委托
    OrderType_BOC = 2,   // 对手方最优价格，深圳证券交易所
    OrderType_BOP = 3,   // 本方最优价格，深圳证券交易所
    OrderType_B5TC = 4,  // 最优五档剩余转撤销，上海/深圳证券交易所
    OrderType_B5TL = 5,  // 最优五档剩余转限价，上海证券交易所
    OrderType_IOC = 6,   // 即时成交剩余转撤销，深圳证券交易所
    OrderType_AON = 7,   // 全额成交或撤销，深圳证券交易所
    OrderType_ALMT = 9,  // 竞价限价，香港证券交易所
    OrderType_ELMT = 10, // 增强限价，香港证券交易所
    OrderType_OLMT = 11, // 零股限价，香港证券交易所
};

// 买卖方向定义
enum OrderSide {
    OrderSide_Bid = 1,                      // 证券、基金、债券普通买入
    OrderSide_Ask = 2,                      // 证券、基金、债券普通卖出
    OrderSide_Buy_Open = 3,                 // 期权买入开仓
    OrderSide_Buy_Close = 4,                // 期权买入平仓
    OrderSide_Sell_Open = 5,                // 期权卖出开仓
    OrderSide_Sell_Close = 6,               // 期权卖出平仓
    OrderSide_Margin_Bid = 13,              // 证券、基金、债券融资买入
    OrderSide_Margin_Ask = 14,              // 证券、基金、债券融券卖出
    OrderSide_Covered_Open = 15,            // 期权备兑开仓
    OrderSide_Covered_Close = 16,           // 期权备兑平仓
    OrderSide_ETF_Create = 17,              // ETF申购
    OrderSide_ETF_Redeem = 18,              // ETF赎回
    OrderSide_Reverse_Repurchase = 19,      // 逆回购
    OrderSide_Margin_EnBuyBack = 20,        // 买券还券
    OrderSide_Margin_EnSellBack = 21,       // 卖券还款
    OrderSide_Margin_StockBack = 22,        // 现券还券
    OrderSide_Margin_PayBack = 23,          // 直接还款
    OrderSide_Margin_MortgageIn = 24,       // 担保品转入
    OrderSide_Margin_MortgageOut = 25,      // 担保品转出
    OrderSide_Repurchase = 26,              // 正回购
    OrderSide_IPO_Bid = 27,                 // 新股申购
    OrderSide_AHFPT_Bid = 28,               // 盘后定价买入
    OrderSide_AHFPT_Ask = 29,               // 盘后定价卖出
    OrderSide_Margin_MoreStockTrans = 30,   // 余券划转
    OrderSide_Allotment_Shares = 31,        // 配股认购
    OrderSide_ETF_Create_OTC = 33,          // 场外ETF申购
    OrderSide_ETF_Redeem_OTC = 34,          // 场外ETF赎回
    OrderSide_Bond_Swap = 35,               // 债券转股
    OrderSide_Bond_Sell_Back = 36,          // 债券回售
    OrderSide_Pledge_In = 37,               // 质押式回购入库
    OrderSide_Pledge_Out = 38,              // 质押式回购出库
};

// 持仓类型
enum PositionSide {
    PositionSide_Long = 1,              // 多仓
    PositionSide_Short = 2,             // 空仓
    PositionSide_Short_Covered = 3,     // 备兑空仓
};

// 成交回报类型定义
enum TradeReportType {
    TradeReportType_Normal = 1,         // 普通回报
    TradeReportType_Cancel = 2,         // 撤单回报
    TradeReportType_Abolish = 3,        // 普通废单回报
    TradeReportType_InsideCancel = 4,   // 内部撤单回报，还未到交易所便被撤下来
    TradeReportType_CancelAbolish = 5,  // 撤单废单回报
};

// 资金账户类型定义
enum AccountType {
    AccountType_Stock = 1,       // 股票
    AccountType_Futures = 2,     // 期货
    AccountType_Options = 3,     // 股票期权
    AccountType_Margin = 4,      // 融资融券
};

// 货币类型
enum CurrencyType {
    CurrencyType_CNY = 1,   // 人民币
    CurrencyType_HKD = 2,   // 港币
    CurrencyType_USD = 3,   // 美元
    CurrencyType_EUR = 4,   // 欧元
    CurrencyType_JPY = 5,   // 日元
    CurrencyType_KRW = 6,   // 韩元
};

// 撤单标识
enum CancelFlag {
    CancelFlag_False = 1,  // 假，不是撤单
    CancelFlag_True = 2,   // 真，是撤单
};

// ETF申购赎回允许状态
enum ETFTradeState {
    ETFTradeState_PurchaseAndRedeem = 1,   // 允许申购和赎回
    ETFTradeState_Forbidden = 2,            // 不允许申购和赎回
    ETFTradeState_OnlyPurchase = 3,         // 表示允许申购、不允许赎回
    ETFTradeState_OnlyRedeem = 4,           // 表示允许赎回、不允许申购
};

// ETF现金替代标识
enum ETFRepalceFlag {
    ETFRepalceFlag_Forbidden = 1,       // 禁止现金替代
    ETFRepalceFlag_Allow = 2,           // 允许现金替代
    ETFRepalceFlag_Must = 3,            // 必须现金替代
    ETFRepalceFlag_NotSHRefund = 4,     // 对于跨市场ETF，表示非沪市股票退补现金替代，此时对应的溢价比例和现金金额部分不能为空
    ETFRepalceFlag_NotSHMust = 5,       // 对于跨市场ETF，表示非沪市股票必须现金替代，对应的现金金额部分不为空。
    ETFRepalceFlag_NotSHSZRefund = 6,   // 非沪深市场成分股退补现金替代，一般是上海跨境ETF对应的成分股
    ETFRepalceFlag_NotSHSZMust = 7,     // 非沪深市场成分股必须现金替代，一般是上海跨境ETF对应的停牌成分股和上海货币ETF-xxxxx1对应值。
};

// 证券类型
enum StkType {
    StkType_Stock = 1,         // 股票
    StkType_Bond = 2,          // 债券
    StkType_Index = 3,         // 指数
    StkType_Future = 4,        // 期货
    StkType_Options = 5,       // 期权
    StkType_Fund = 6,          // 基金
    StkType_Repurchase = 7,    // 回购
    StkType_Warrant = 8,       // 权证
    StkType_STIB = 9,          // 科创板股票
};

// 证券类型详细
enum SecurityTypeDetail {
    SecurityTypeDetail_Default = 0,        // 默认类型
    SecurityTypeDetail_ZBAG = 1,           // 主板A股
    SecurityTypeDetail_ZXBG = 2,           // 中小板股票
    SecurityTypeDetail_CYBG = 3,           // 创业板股票
    SecurityTypeDetail_ZBBG = 4,           // 主板B股
    SecurityTypeDetail_GZ = 5,             // 国债（含地方债）
    SecurityTypeDetail_QYZ = 6,            // 企业债  
    SecurityTypeDetail_GSZ = 7,            // 公司债
    SecurityTypeDetail_KZZ = 8,            // 可转债
    SecurityTypeDetail_SMZ = 9,            // 私募债
    SecurityTypeDetail_KJHSMZ = 10,        // 可交换私募债
    SecurityTypeDetail_ZQGSCJZ = 11,       // 证券公司次级债
    SecurityTypeDetail_ZYSHG = 12,         // 质押式回购
    SecurityTypeDetail_ZCZCZQ = 13,        // 资产支持证券
    SecurityTypeDetail_GPETF = 14,         // 股票ETF
    SecurityTypeDetail_KSCGPETF = 15,      // 跨市场股票ETF
    SecurityTypeDetail_KJETF = 16,         // 跨境ETF
    SecurityTypeDetail_SWZQETF = 17,       // 实物债券ETF
    SecurityTypeDetail_XJZQETF = 18,       // 现金债券ETF
    SecurityTypeDetail_HJETF = 19,         // 黄金ETF
    SecurityTypeDetail_HBETF = 20,         // 货币ETF
    SecurityTypeDetail_GGETF = 21,         // 杠杆ETF
    SecurityTypeDetail_SPQHETF = 22,       // 商品期货ETF
    SecurityTypeDetail_BZLOF = 23,         // 标准LOF
    SecurityTypeDetail_FJZJJ = 24,         // 分级子基金
    SecurityTypeDetail_FBSJJ = 25,         // 封闭式基金
    SecurityTypeDetail_JSSJJ = 26,         // 仅申赎基金
    SecurityTypeDetail_PSQZ = 27,          // 配售权证
    SecurityTypeDetail_QZ = 28,            // 权证
    SecurityTypeDetail_GGQQ = 29,          // 个股期权
    SecurityTypeDetail_ETFQQ = 30,         // ETF期权
    SecurityTypeDetail_ZGCP = 31,          // 资管产品
    SecurityTypeDetail_BJHG = 32,          // 报价回购
    SecurityTypeDetail_YXG = 33,           // 优先股
    SecurityTypeDetail_ZQGSDQZ = 34,       // 证券公司短期债
    SecurityTypeDetail_KJHGSZ = 35,        // 可交换公司债
    SecurityTypeDetail_ZQFX = 36,          // 债券分销
    SecurityTypeDetail_GZFX = 37,          // 国债分销
    SecurityTypeDetail_QTZQ = 38,          // 其他债券
    SecurityTypeDetail_KSC = 39,           // 跨市场/跨境资金
    SecurityTypeDetail_QTJJ = 40,          // 其他基金
    SecurityTypeDetail_GJBGP = 41,         // 国际版股票
    SecurityTypeDetail_QTGP = 42,          // 其他股票
    SecurityTypeDetail_MDSZQHG = 43,       // 买断式债券回购
    SecurityTypeDetail_CYBKZZ = 44,        // 创业板可转债
    SecurityTypeDetail_CTPZ = 45,          // 存托凭证
    SecurityTypeDetail_HLTCDR = 46,        // 沪伦通CDR
    SecurityTypeDetail_CXQYGP = 47,        // 创新企业股票
    SecurityTypeDetail_ZYDM = 48,          // 质押代码
    SecurityTypeDetail_SSSSHBJJ = 49,      // 实时申赎货币基金
    SecurityTypeDetail_XGXZFX = 50,        // 新股新债发行
    SecurityTypeDetail_KCB = 51,           // 科创板
    SecurityTypeDetail_KCBCDR = 53,        // 科创板CDR
};

// 证券状态
enum SecurityStatus {
    SecurityStatus_Normal = 0,                  // 正常
    SecurityStatus_Suspend = 1,                 // 停牌
    SecurityStatus_NearExpireDate = 2,          // 临近到期日
    SecurityStatus_Adjustment = 3,              // 最近5个交易日内发生调整
    SecurityStatus_ExcludeRight = 4,            // 除权
    SecurityStatus_ExcludeDividend = 5,         // 除息
    SecurityStatus_Caution = 6,                 // 风险警示
    SecurityStatus_IPOFirstDay = 7,             // 上市首日
    SecurityStatus_Delisting = 8,               // 退市整理期
    SecurityStatus_TransferByAgreement = 9,     // 退市后协议转让
};

// 柜台类型
enum CounterType {
    CounterType_JZJY = 1,               // 集中交易柜台
    CounterType_APEX_MARGIN = 2,        // 顶点两融HTS柜台
    CounterType_APEX = 3,               // 顶点快速柜台
    CounterType_DYC = 5,                // 君睿股票快速柜台
    CounterType_DYC_MARGIN = 6,         // 君睿两融快速柜台
    CounterType_DYC_JZJY = 8,           // 君睿股票集中柜台
    CounterType_DYC_JZJY_MARGIN = 9,    // 君睿两融集中柜台
};

// 常用股东权限类型
enum SecuidRight {
    SecuidRight_Delisting = 1,              // 退市整理
    SecuidRight_Caution = 2,                // 风险警示
    SecuidRight_Gem = 3,                    // 创业板
    SecuidRight_KeChuangPlate_Normal = 4,   // 科创版权限_普通账号
    SecuidRight_KeChuangPlate_Credit = 5,   // 科创版权限_信用账号
    SecuidRight_Repo = 6,                   // 债券回购-正回购
    SecuidRight_Reverse_Repo = 7,           // 债券回购-逆回购
    SecuidRight_SHHK_Trade = 8,             // 沪港通
    SecuidRight_SZHK_Trade = 9,             // 深港通
    SecuidRight_ETF_Redemption_Normal = 10, // 普通ETF申赎
    SecuidRight_Hulun_Trade = 11,           // 沪伦通交易
};

// 柜台间资金划转方向
enum TransferFundSide {
    TransferFundSide_In = 1,    // 资金转入，从集中交易柜台转入到快速柜台
    TransferFundSide_Out = 2,   // 资金转出，从快速柜台转出到集中交易柜台
};

// 风控告警消息类型
struct RiskNotify {
    char secuid[LEN_ID];            // 证券账户(股东代码)
    char alarm_score[LEN_ID];       // 告警指数值
    char alarm_status[LEN_ID];      // 告警状态
    char alarm_rule[LEN_ID];        // 告警规则名称
    char alarm_time[LEN_ID];        // 告警时间
    char alarm_msg[LEN_ERR_MSG];    // 告警内容详情
};

// 委托属性
enum OrderFlag {
    OrderFlag_Security_Normal = 1,              // 证券普通交易
    OrderFlag_Security_CashLoan = 2,            // 证券融资交易
    OrderFlag_Security_SecurityLoan = 3,        // 证券融券交易
    OrderFlag_Future_Option_Speculation = 4,    // 期货/期权投机
    OrderFlag_Future_Option_Hedge = 5,          // 期货/期权套期保值
    OrderFlag_Future_Option_Arbitrage = 6,      // 期货/期权套利
    OrderFlag_Option_Covered = 7,               // 期权备兑交易
};

// 委托查询标志位
enum OrderQueryFlag {
    OrderQueryFlag_All = 0,         // 查询所有委托
    OrderQueryFlag_Cancelable = 1,  // 查询可撤单委托
    OrderQueryFlag_NonCancel = 2,   // 查询非撤单委托
};

// 新发行证券查询标志位
enum IPOQueryFlag {
    IPOQueryFlag_NewStock = 1,      // 查询新股信息
    IPOQueryFlag_NewBond = 2,       // 查询新债信息
};

// 行权执行类型定义
enum ExerciseType {
    ExerciseType_Execute = 1,     // 执行
};

// 行权操作状态类型定义
enum ExerciseOperateStatus {
    ExerciseOperateStatus_InsertSubmitted = 1,   // 已经提交
    ExerciseOperateStatus_CancelSubmitted = 2,   // 撤单已经提交
    ExerciseOperateStatus_Accepted = 3,          // 已经接受
    ExerciseOperateStatus_InsertRejected = 4,    // 报单已经被拒绝
    ExerciseOperateStatus_CancelRejected = 5,    // 撤单已经被拒绝
    ExerciseOperateStatus_UnSubmitted = 6,       // 未提交
};

// 行权状态类型定义
enum ExerciseStatus {
    ExerciseStatus_SendStock = 1,       // 发往现货系统
    ExerciseStatus_RepealStock = 2,     // 冲正现货系统
    ExerciseStatus_SendOffer = 3,       // 发往报盘
    ExerciseStatus_Fail = 4,            // 行权失败
    ExerciseStatus_Accepted = 5,        // 交易所已接收
    ExerciseStatus_Cancelled = 6,       // 行权已撤销
};

// 执行方式
enum StrikeModeType {
    StrikeModeType_Continental = 1,   // 欧式
    StrikeModeType_American = 2,      // 美式
    StrikeModeType_Bermuda = 3,       // 百慕大
};

// 期权类型
enum OptionsType {
    OptionsType_CallOptions = 1,   // 看涨
    OptionsType_PutOptions = 2,    // 看跌
};

// 申报单位
enum OrderUnitType {
    OrderUnitType_Shou = 1,          // 手
    OrderUnitType_Gu = 2,            // 股
    OrderUnitType_Fen = 3,           // 份
    OrderUnitType_Zhang = 4,         // 张
};

// 转移状态
enum TransferStatus {
    TransferStatus_TransferHandling = 1,    // 转移正在处理
    TransferStatus_TransferSuccess = 2,     // 转移成功
    TransferStatus_TransferFail = 3,        // 转移失败
};

// 现货持仓转划转型
enum TransferPositionType {
    TransferPositionType_All = 1,       // 任意仓
    TransferPositionType_History = 2,   // 昨仓
    TransferPositionType_TodayBS = 3,   // 今买卖仓
    TransferPositionType_TodayPR = 4,   // 今申赎仓
};

// 现货持仓划转方向
enum TransferStockPositionSide {
    TransferStockPositionSide_In = 1,                    // 蓝补
    TransferStockPositionSide_Out = 2,                   // 红冲
    TransferStockPositionSide_MoveIn = 3,                // 调入
    TransferStockPositionSide_MoveOut = 4,               // 调出
    TransferStockPositionSide_Lock = 5,                  // 备兑锁定
    TransferStockPositionSide_Unlock = 6,                // 备兑解锁
    TransferStockPositionSide_ExerciseFreeze = 7,        // 行权冻结
    TransferStockPositionSide_ExerciseUnfreeze = 8,      // 行权失败解冻
    TransferStockPositionSide_CoveredCloseUnfreeze = 9,  // 备兑平仓释放
};

// 期权现货锁定类型
enum LockStockType {
    LockStockType_Lock = 1,             // 锁定
    LockStockType_Unlock = 2,           // 解锁
};

// 期权现货锁定状态
enum LockStockStatus {
    LockStockStatus_SendStock = 1,      // 发往现货系统
    LockStockStatus_RepealStock = 2,    // 发往现货系统冲正
    LockStockStatus_SendOffer = 3,      // 锁定/解锁被期权系统接收后往期权报盘发送
    LockStockStatus_Fail = 4,           // 锁定/解锁失败
    LockStockStatus_Success = 5,        // 锁定/解锁成功
    LockStockStatus_ForceCancel = 6,    // 强制撤销，锁定委托被管理员撤销，用在期权报盘工作异常的特殊场景
};

// 期权合约状态定义，目前仅深圳期权有
// 每个状态位使用整数的bit位表示，如果bit位为1，表示为此状态，一个合约可能处于多个状态
enum ContractStatus {
    ContractStatus_Suspend = 0x00000001,                // 停牌
    ContractStatus_LongTermSuspend = 0x00000002,        // 长期停牌
    ContractStatus_CircuitBreaker = 0x00000040,         // 熔断机制
                                                        //   bit位为1: 不接受新订单申报
                                                        //   bit位为0: 接受新订单申报
    ContractStatus_RestrictLongOpen = 0x00000080,       // 限制买入开仓
    ContractStatus_RestrictShortOpen = 0x00000100,      // 限制卖出（不包括备兑）开仓
    ContractStatus_RestrictCoveredOpen = 0x00000200,    // 限制备兑开仓
    ContractStatus_VolatilityInterrupt = 0x00000400,    // 波动性中断
    ContractStatus_TempSuspend = 0x00000800,            // 临时停牌
    ContractStatus_ContinuousSuspend = 0x00001000,      // 连续停牌
    ContractStatus_RestrictExercise = 0x00002000,       // 限制行权
    ContractStatus_RestrictMakerQuote = 0x00004000,     // 限制做市商报价
};

// 组合报单类型
enum OptionCombineType {
    OptionCombineType_Combine = 1,          // 组合
    OptionCombineType_Split = 2,            // 拆分
    OptionCombineType_ForceSplit = 3,       // 强拆
};

// 组合策略类型
enum OptionCombineStrategy {
    OptionCombineStrategy_CNSJC = 1,        // 认购牛市价差策略
    OptionCombineStrategy_CXSJC = 2,        // 认购熊市价差策略
    OptionCombineStrategy_PXSJC = 3,        // 认沽熊市价差策略
    OptionCombineStrategy_PNSJC = 4,        // 认沽牛市价差策略
    OptionCombineStrategy_KS = 5,           // 跨式空头
    OptionCombineStrategy_KKS = 6,          // 宽跨式空头
    OptionCombineStrategy_ZBD = 7,          // 保证金开仓转备兑
};

// 展期审批状态
enum ApprovalStatus {
    ApprovalStatus_NoCheck = 1,     // 未审批
    ApprovalStatus_CheckSucc = 2,   // 审批通过
    ApprovalStatus_CheckFail = 3,   // 审批不过
    ApprovalStatus_Expired = 4,     // 过期作废
    ApprovalStatus_Cancelled = 5,   // 已撤单
    ApprovalStatus_Extended = 6,    // 已展期处理
};

// 下单的请求类型
struct OrderReq {
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，可不传
    char symbol[LEN_SYMBOL];    // 交易标的，格式为市场.证券ID或市场.合约ID，例如SH.600000或SHOP.10002003
    int16_t order_type;         // 订单类型，参考OrderType定义，新股申购填限价
    int16_t side;               // 买卖方向，参考OrderSide定义
    int64_t volume;             // 订单数量，股票单位（股），债券单位（上海：手，深圳：张）
    int64_t price;              // 订单委托价，限价单使用，扩大一万倍，市价填写0
    int16_t order_flag;         // 委托属性，参考OrderFlag定义
};

// 下单的应答类型
struct OrderRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int32_t order_date;         // 系统生成的订单日期(夜市委托则返回下一个交易日)
    char order_id[LEN_ID];      // 系统生成的订单id
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，原样返回
};

// 撤单的请求类型
struct CancelReq {
    char order_id[LEN_ID];      // 被撤的原订单id
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，可不传
    char cl_cancel_id[LEN_ID];  // 客户端撤单id，用来引用一个撤单订单，由用户自定义，可不传
};

// 撤单的应答类型
struct CancelRsp {
    char account_id[LEN_ID];        // 交易账号，目前是资金账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char order_id[LEN_ID];          // 被撤的原订单id
    char cl_order_id[LEN_ID];       // 客户端订单id，用来引用一个普通订单，由用户自定义，原样返回
    char cl_cancel_id[LEN_ID];      // 客户端撤单id，用来引用一个撤单订单，由用户自定义，原样返回
};

// 订单明细数据
struct OrderDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char order_id[LEN_ID];      // 系统生成的订单id，对于撤单是系统撤单id
    char cl_order_id[LEN_ID];   // 客户端订单id，对应到客户端的原订单id
    char orig_order_id[LEN_ID]; // 仅撤单订单使用，是被撤的原订单id
    char symbol[LEN_SYMBOL];    // 交易标的，格式为市场.证券ID或市场.合约ID
    int16_t order_status;       // 订单状态，参考OrderStatus定义
    int16_t order_type;         // 订单类型，参考OrderType定义
    int16_t side;               // 买卖方向，参考OrderSide定义
    int64_t volume;             // 订单数量，股票单位（股），债券单位（上海：手，深圳：张）
    int64_t price;              // 订单委托价，扩大一万倍
    int64_t filled_volume;      // 订单累计已完成数量
    int64_t filled_turnover;    // 订单累计已完成金额，扩大一万倍
    int64_t filled_price;       // 成交均价，扩大一万倍
    int64_t cancel_volume;      // 撤单数量
    int16_t cancel_flag;        // 撤单标识，参考CancelFlag定义
    int32_t order_date;         // 订单日期，格式为YYYYMMDD
    int32_t order_time;         // 订单时间，格式为HHMMSSmmm，对于订单状态推送，是推送时间点
    int32_t err_code;           // 下单失败时的错误码
    char err_msg[LEN_ERR_MSG];  // 下单失败时的错误消息，Windows是GBK，Linux是UTF8
    char secuid[LEN_ID];        // 证券账户(股东代码)
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int64_t freeze_amount;      // 冻结金额
};

// 成交明细数据
struct TradeDetail {
    char account_id[LEN_ID];        // 交易账号，目前是资金账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char order_id[LEN_ID];          // 系统生成的订单id，对于撤单是系统原订单id
    char cl_order_id[LEN_ID];       // 客户端订单id，对应到客户端的原订单id
    char symbol[LEN_SYMBOL];        // 交易标的，格式为市场.证券ID或市场.合约ID
    int16_t order_type;             // 订单类型，参考OrderType定义
    int16_t side;                   // 买卖方向，参考OrderSide定义
    int16_t report_type;            // 成交回报类型，参考TradeReportType定义
    char report_no[LEN_ID];         // 成交编号
    int64_t volume;                 // 成交数量，当report_type不是TradeReportType_Normal时代表撤单或废单数量
    int64_t price;                  // 成交价格，扩大一万倍
    int64_t turnover;               // 成交金额，扩大一万倍
    int32_t trade_date;             // 成交日期，格式为YYYYMMDD
    int32_t trade_time;             // 成交时间，格式为HHMMSSmmm
    int32_t err_code;               // 下单失败时的错误码
    char err_msg[LEN_ERR_MSG];      // 下单失败时的错误消息，Windows是GBK，Linux是UTF8
    char secuid[LEN_ID];            // 证券账户(股东代码)
    char name[LEN_SYMBOL_NAME];     // 证券名称
};

// 仓位明细数据
struct PositionDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];    // 持仓标的，格式为市场.证券ID或市场.合约ID
    int16_t side;               // 持仓方向，参考PositionSide定义
    int64_t volume;             // 总持仓量
    int64_t avail_volume;       // 可用持仓量
    int64_t init_volume;        // 日初持仓量
    int64_t market_value;       // 仓位市值，扩大一万倍
    int64_t today_buy_volume;   // 今日买入成交数量，仅顶点柜台有效
    int64_t today_sell_volume;  // 今日卖出成交数量，仅顶点柜台有效
    char secuid[LEN_ID];        // 证券账户(股东代码)
    int32_t cost_price;             // 成本价
    int64_t buy_cost;               // 成本金额
    int32_t last_price;             // 最新价
    int64_t income;                 // 浮动盈亏
    int64_t total_income;           // 累计盈亏
    int64_t profit_cost;            // 持仓成本(盈亏成本)
    int64_t today_avail_pr_volume;  // 可申赎数量，仅君睿柜台
    int32_t market;                 // 市场，参考MarketType定义
    int32_t security_type;          // 证券类别，参考SecurityTypeDetail定义，仅君睿柜台
    int64_t freeze_volume;          // 冻结数量，仅顶点柜台有效
    char name[LEN_SYMBOL_NAME];     // 证券名称
};

// 资金明细数据
struct CashDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    int64_t total_amount;       // 总资金量，扩大一万倍
    int64_t avail_amount;       // 可用资金，扩大一万倍
    int64_t total_asset;        // 总资产，扩大一万倍
    int64_t market_value;       // 证券市值，扩大一万倍
};

// 交易账户相关信息
struct AccountInfo {
    char account_id[LEN_ID];        // 交易账号，目前是资金账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char account_pwd[LEN_ID];       // 交易账号密码
    char cust_orgid[LEN_ID];        // 交易账号的机构编码
    char cust_branchid[LEN_ID];     // 交易账号的分支编码
    char cl_system_id[LEN_SYS_ID];  // 接入方系统标识，由服务端分配
};

// 资金账号对应的股东账号信息
struct SecuidInfo {
    char market[LEN_MARKET];        // 市场，SH、SZ等，参考本文件中定义
    char secuid[LEN_ID];            // 证券账户(股东代码)
	char bank_code[LEN_ORG_ID];		// 银行代码
};

// 登录应答数据
struct LoginRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char cust_orgid[LEN_ID];    // 交易账号的机构编码
    char cust_branchid[LEN_ID]; // 交易账号的分支编码
    char cust_id[LEN_ID];       // 客户号
    char cust_name[LEN_ID];     // 客户姓名
    SecuidInfo secuid_array[2]; // 股东代码列表
    char cif_account[LEN_ID];   // 一户通账号
};

// ETF基本信息明细
struct ETFDetail {
    char name[LEN_SYMBOL_NAME];     // ETF名称
    char first_symbol[LEN_SYMBOL];  // 一级市场代码，格式为市场.证券ID或市场.合约ID
    char second_symbol[LEN_SYMBOL]; // 二级市场代码，格式为市场.证券ID或市场.合约ID
    int32_t trade_unit;             // 最小申赎份额
    int64_t cash_component;         // 预估现金差额，扩大一万倍
    int64_t max_cash_ratio;         // 最大现金替代比例，扩大一万倍
    int32_t trade_state;            // 申购赎回允许状态，参考ETFTradeState定义
    int32_t record_num;             // 股票篮子记录数
    int32_t trade_day;              // T日日期
    int32_t pre_trade_day;          // T-1日日期
    int64_t nav_percu;              // T-1日申赎基准单位净值，扩大一万倍
    int64_t nav;                    // T-1日基金单位净值，扩大一万倍

    // 以下字段仅深圳ETF有效,为0表示没有限制
    int64_t creation_limituser;         // 单帐户当天累计可申购的基金份额上限
    int64_t redemption_limituser;       // 单帐户当天累计可赎回的基金份额上限
    int64_t net_creation_limituser;     // 单账户当天净申购的基金份额上限
    int64_t net_redemption_limituser;   // 单账户当天净赎回的基金份额上限
    int64_t creation_limit;             // 当天累计可申购的基金份额上限
    int64_t redemption_limit;           // 当天累计可赎回的基金份额上限
    int64_t net_creation_limit;         // 当天净申购的基金份额上限
    int64_t net_redemption_limit;       // 当天净赎回的基金份额上限
};

// ETF股票篮子明细
struct ETFStockDetail {
    char first_symbol[LEN_SYMBOL];  // ETF一级市场代码，格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME];     // 证券名称
    char symbol[LEN_SYMBOL];        // 证券代码，格式为市场.证券ID或市场.合约ID
    int32_t volume;                 // 股份数量
    int16_t replace_flag;           // 现金替代标识，参考ETFRepalceFlag定义
    int64_t over_price_rate;        // 溢价比例，扩大一万倍
    int64_t replace_amt;            // 现金替代金额，扩大一万倍
};

// 最大可委托数量数据
struct MaxOrderQtyDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int64_t max_qty;            // 最大可委托数量，最大限制100万
    int64_t actual_max_qty;     // 实际最大可委托数量，可能超过100万
};

// 新股可申购额度数据
struct IPOMaxPurchaseDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char market[8];             // 市场，SH、SZ等，参考本文件中定义
    int64_t max_qty;            // 申购额度
    int64_t stib_max_qty;       // 科创板申购额度
};

// 新股数据
struct IPOStockDetail {
    char symbol[LEN_SYMBOL];    // 格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    int64_t ipo_price;          // 发行价，扩大一万倍
    int64_t max_num;            // 最高交易数量
    int64_t min_num;            // 最低交易数量
};

// 新股配号数据
struct IPODistributionDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int32_t biz_date;           // 配号日期
    char symbol[LEN_SYMBOL];    // 格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    char mate_no[LEN_ID];       // 申购配号
    int64_t match_qty;          // 成交数量
};

//  中签数据
struct IPOLotteryDetail {
    char account_id[LEN_ID];    // 交易账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int32_t biz_date;           // 中签日期
    char symbol[LEN_SYMBOL];    // 格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int64_t match_price;        // 成交价格，扩大一万倍
    int64_t match_qty;          // 成交数量
};

// 证券基本信息查询数据
struct SecurityBaseInfo {
    char symbol[LEN_SYMBOL];       // 格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME];    // 证券名称
    int32_t security_type;         // 证券类型，参考SecurityTypeDetail定义
    int32_t security_status;       // 证券状态，参考SecurityStatus定义
    int64_t price_tick;            // 证券价位
    int64_t limit_up;              // 涨停价格
    int64_t limit_down;            // 跌停价格
    int64_t max_qty;               // 最大数量
    int64_t min_qty;               // 最小数量
    int64_t buy_tick;              // 买入最小单位
    int64_t sale_tick;             // 卖出最小单位 
    int32_t has_price_limit;       // 是否有涨幅控制1=True/Yes,0=False/No
    int32_t max_rise_rate;         // 最大涨幅
    int32_t is_registration;       // 是否注册制1=True/Yes,0=False/No
};

// 沪港通参考汇率数据
struct HKRateDetail {
    char market[8];     // 市场，SH、SZ等，参考本文件中定义
    int64_t buy_rate;   // 买入参考汇率，扩大一万倍
    int64_t sale_rate;  // 卖出参考汇率，扩大一万倍
    int64_t mid_rate;   // 中间参考汇率，扩大一万倍
    int64_t set_rate;   // 结算汇率，扩大一万倍
    int32_t sys_date;   // 更新日期
};

// 沪港通标的券数据
struct HKStockDetail {
    char symbol[LEN_SYMBOL];    // 格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int16_t stktype;            // 证券类型，参考StkType定义
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
};

//  沪港通辅资金表资产数据
struct HKFundDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    int64_t fund_uncomeavl;     // 港股在途可用资金，扩大一万倍
    int64_t fund_buy;           // 港股资金买入冻结，扩大一万倍
    int64_t fund_sale;          // 港股资金卖出解冻，扩大一万倍
    int64_t fund_uncomebuy;     // 港股资金在途买入，扩大一万倍
    int64_t fund_uncomesale;    // 港股资金在途卖出，扩大一万倍
};

//  沪港通最小价差数据
struct HKMinPriceUnitDetail {
    int16_t stktype;        // 证券类型，参考StkType定义
    int64_t begin_price;    // 区间起始价格，扩大一万倍
    int64_t end_price;      // 区间终止价格，扩大一万倍
    int32_t price_unit;     // 区间最小价格单位，数值的单位为厘即1/1000元
};

//  沪港通交易日历数据
struct HKTradeCalendarDetail {
    int32_t date;           // 日期
    int16_t business_flag;  // 交易日标识，0表示交易日，1表示非交易日
    int16_t commit_flag;    // 交收日标识，0表示交收日，1表示非交收日
};

// 担保品转入转出请求类型
struct CreditMortgageInOutReq {
    char cl_order_id[LEN_ID];   // 客户端订单id，由用户自定义，用来引用一个普通订单
    char symbol[LEN_SYMBOL];    // 交易标的，格式为市场.证券ID或市场.合约ID
    int16_t side;               // 买卖方向，参考OrderSide定义，
                                // 担保品转入传OrderSide_Margin_MortgageIn，
                                // 担保品转出传OrderSide_Margin_MortgageOut
    int32_t volume;             // 担保品划转数量
};

// 担保品转入转出应答类型
struct CreditMortgageInOutRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char cl_order_id[LEN_ID];   // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];      // 系统生成的订单id
};

// 现券还券请求类型
struct CreditStockBackReq {
    char cl_order_id[LEN_ID];   // 客户端订单id，由用户自定义，用来引用一个普通订单
    char symbol[LEN_SYMBOL];    // 交易标的，格式为市场.证券ID或市场.合约ID
    int32_t volume;             // 还券数量
};
// 现券还券应答类型
struct CreditStockBackRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char cl_order_id[LEN_ID];   // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];      // 系统生成的订单id
};

// 直接还款应答类型
struct CreditPayBackRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int64_t real_back_amt;      // 实际还款金额，扩大一万倍
};

// 信用标的券数据
struct CreditStockDetail {
    char symbol[LEN_SYMBOL];    // 标的券，格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    char credit_fund_ctrl;      // 融资允许，'0'-允许，'1'-禁止
    char credit_stk_ctrl;       // 融券允许，'0'-允许，'1'-禁止
    int64_t margin_rate_fund;   // 融资保证金比例，扩大一万倍
    int64_t margin_rate_stk;    // 融券保证金比例，扩大一万倍
    int32_t sep_rem_qty;        // 融券专户余券
};

// 信用资产数据
struct CreditAssetsDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    int64_t avail_balance;      // 可用自有资金，即可买担保品资金，扩大一万倍
    int64_t fetch_balance;      // 可取资金，扩大一万倍
    int64_t frozen_balance;     // 冻结资金，扩大一万倍
    int64_t stock_balance;      // 证券市值，扩大一万倍
    int64_t fund_balance;       // 总资金，扩大一万倍
    int64_t asset_balance;      // 总资产，扩大一万倍
    int64_t avail_margin;       // 可用保证金，扩大一万倍
    int64_t credit_quota;       // 授信额度，扩大一万倍
    int64_t finance_quota;      // 可融资额度，扩大一万倍
    int64_t shortsell_quota;    // 可融券额度，扩大一万倍
    int64_t assure_ratio;       // 维持担保比例，扩大一万倍
    int64_t total_debt;         // 总负债，扩大一万倍
    int64_t fund_debt;          // 融资负债金额，包含融资利息及费用，扩大一万倍
    int64_t stock_debt;         // 融券负债金额，包含融券利息及费用，扩大一万倍
    int64_t fund_interest_fee;  // 融资利息及费用，扩大一万倍
    int64_t stock_interest_fee; // 融券利息及费用，扩大一万倍
    int64_t shortsell_total_balance;        // 融券卖出总资金，扩大一万倍
    int64_t shortsell_avail_balance;        // 融券卖出可用资金（仅君睿柜台），扩大一万倍
    int64_t shortsell_frozen_balance;       // 融券卖出冻结资金（仅君睿柜台），扩大一万倍
    int64_t enbuyback_avail_balance;        // 可买券还券资金，扩大一万倍
    int64_t fund_margin_profit;             // 融资盈亏，扩大一万倍
    int64_t stock_margin_profit;            // 融券盈亏，扩大一万倍
    int64_t fund_interest;                  // 融资利息，扩大一万倍
    int64_t stock_interest;                 // 融券利息，扩大一万倍
    int64_t fund_margin_balance;            // 融资市值，扩大一万倍
    int64_t stock_margin_balance;           // 融券市值，扩大一万倍
    int64_t fund_floating_deficit;          // 融资浮亏，扩大一万倍
    int64_t stock_floating_deficit;         // 融券浮亏，扩大一万倍
    int64_t fund_margin_profit_conversion;  // 融资盈亏折算，扩大一万倍
    int64_t stock_margin_profit_conversion; // 融券盈亏折算，扩大一万倍
};

// 融资合约数据
struct CreditFinanceDetail {
    char account_id[LEN_ID];        // 交易账号，目前是资金账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];        // 交易标的，格式为市场.证券ID
    char name[LEN_SYMBOL_NAME];     // 证券名称
    char order_id[LEN_ID];          // 系统生成的订单id
    int16_t currency_type;          // 货币类型
    int16_t debt_status;            // 负债现状，0：未了结，1：已了结
    int32_t occur_date;             // 合约的发生日期
    int64_t total_balance;          // 合约的总金额，扩大一万倍
    int64_t cur_balance;            // 合约的当前未偿还金额，扩大一万倍
    int64_t total_interest_fee;     // 合约的利息及费用总金额，扩大一万倍
    int64_t cur_interest_fee;       // 合约的当前未偿还利息及费用金额，扩大一万倍
    int64_t interest_rate;          // 利率，扩大一万倍
    int64_t repayable_balance;      // 可还款金额，扩大一万倍
    int64_t f_deal_bal;             // 期初应付融资款余额
    int64_t f_exp_cet_intr;         // 期初应付负债息费
    int64_t credit_repay_unfrz;     // 当日归还负债金额
    int64_t all_fee_unfrz;          // 当日归还负债息费
    int32_t market;                 // 市场
};

// 融券合约数据类型
struct CreditShortsellDetail {
    char account_id[LEN_ID];        // 交易账号，目前是资金账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];        // 交易标的，格式为市场.证券ID
    char name[LEN_SYMBOL_NAME];     // 证券名称
    char order_id[LEN_ID];          // 系统生成的订单id
    int16_t currency_type;          // 货币类型，参考CurrencyType定义
    int16_t debt_status;            // 负债现状，0：未了结，1：已了结
    int32_t occur_date;             // 合约的发生日期
    int64_t total_qty;              // 合约的融券总数量
    int64_t cur_qty;                // 合约的当前未偿还融券数量
    int64_t total_interest_fee;     // 合约的利息及费用总金额，扩大一万倍
    int64_t cur_interest_fee;       // 合约的当前未偿还利息及费用金额，扩大一万倍
    int64_t interest_rate;          // 利率，扩大一万倍
    int64_t d_stk_bal;              // 期初应偿还融券总数
    int32_t market;                 // 市场
    int64_t all_fee_unfrz;          // 当日归还负债息费
    int64_t stk_repay_unfrz;        // 当日归还负债数量
    int32_t end_date;               // 负债截至日期
};

// 可还融资负债金额数据
struct CreditRepayAmountDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int64_t max_back_amt;       // 可还款金额，扩大一万倍
};

// 信用融券负债数量数据
struct CreditRepayStockDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];    // 持仓标的，格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int64_t total_qty;          // 融券负债总数量
    int64_t max_back_qty;       // 可还券数量
    int64_t returned_qty;       // 已还券数量（包括现券还券、买券还券数量）
};

// 担保品券数据
struct CreditMortgageHoldDetail {
    char account_id[LEN_ID];    // 交易账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];    // 标的券，格式为市场.证券ID或市场.合约ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    int64_t pledge_rate;        // 折算率，扩大一万倍
};

// 查询锁定的可融券数量的应答类型
struct CreditSecuritySellQtyRsp {
    char account_id[LEN_ID];    // 交易账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];    // 证券代码，格式为市场.证券ID或市场.合约ID
    int64_t total_qty;          // 证券数量，指锁券的总数量
    int64_t avail_qty;          // 证券可用剩余数量，指锁券的可用数量
};


// 期权资金明细数据
struct OptionCashDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int16_t currency_type;      // 货币类型，参考CurrencyType定义
    int64_t init_amount;        // 日初资金，扩大一万倍
    int64_t total_amount;       // 总资金量，扩大一万倍
    int64_t avail_amount;       // 可用资金，扩大一万倍
    int64_t fetch_amount;       // 可取资金，扩大一万倍
    int64_t frozen_amount;      // 冻结资金，权利金委托冻结，扩大一万倍
    int64_t used_margin;        // 实时占用的保证金，包含未成交义务仓委托的冻结保证金，扩大一万倍
    int64_t exercise_frozen;    // 行权冻结资金，扩大一万倍
    int64_t deposit_amount;     // 入金金额，扩大一万倍
    int64_t withdraw_amount;    // 出金金额，扩大一万倍
    int64_t royalty_in;         // 权利金收入，扩大一万倍
    int64_t royalty_out;        // 权利金支出，扩大一万倍
    int64_t commission;         // 手续费，扩大一万倍
    int64_t frozen_commission;  // 冻结手续费，扩大一万倍
};

// 期权持仓明细数据
struct OptionPositionDetail {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];    // 持仓标的，格式为市场.证券ID或市场.合约ID
    int16_t side;               // 持仓方向，参考PositionSide定义
    int64_t init_volume;        // 日初持仓量，包含组合占用持仓
    int64_t init_avail_volume;  // 日初可用持仓量
    int64_t init_comb_volume;   // 日初已组合持仓量
    int64_t volume;             // 总持仓量，包含组合占用持仓
    int64_t avail_volume;       // 可用持仓量
    int64_t comb_volume;        // 已组合持仓量
    int64_t open_volume;        // 开仓数量
    int64_t close_volume;       // 平仓数量
    int64_t exercise_frozen;    // 行权冻结数量，包含合并行权冻结数量
    int64_t buy_cost;           // 持仓成本
    char secuid[LEN_ID];        // 证券账户(股东代码)
};

// 行权的请求类型
struct ExerciseReq {
    char cl_order_id[LEN_ID];   // 客户端订单id，由用户自定义，用来引用一个普通订单
    char symbol[LEN_SYMBOL];    // 交易标的，格式为市场.证券ID或市场.合约ID
    int64_t volume;             // 数量
    int16_t exercise_type;      // 执行类型，参考ExerciseType定义
};

// 行权的响应类型
struct ExerciseRsp {
    char account_id[LEN_ID];        // 交易账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char cl_order_id[LEN_ID];       // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];          // 柜台行权委托编号
    int16_t exercise_type;          // 执行类型，参考ExerciseType定义
};

// 撤销行权请求类型
struct CancelExerciseReq {
    char order_id[LEN_ID];          // 柜台行权委托编号
    char cl_order_id[LEN_ID];       // 客户端订单id，用来引用一个普通订单，由用户自定义，可不传
    char cl_cancel_id[LEN_ID];      // 客户端撤单id，用来引用一个撤单订单，由用户自定义，可不传
};

// 撤销行权响应类型
struct CancelExerciseRsp {
    char account_id[LEN_ID];        // 交易账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char order_id[LEN_ID];          // 柜台行权委托编号
    char cl_order_id[LEN_ID];       // 客户端订单id，用来引用一个普通订单，由用户自定义，原样返回
    char cl_cancel_id[LEN_ID];      // 客户端撤单id，用来引用一个撤单订单，由用户自定义，原样返回
};

// 行权委托明细
struct ExerciseDetail {
    char account_id[LEN_ID];        // 交易账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    int16_t exercise_type;          // 执行类型，参考ExerciseType定义
    char cl_order_id[LEN_ID];       // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];          // 柜台行权委托编号
    int32_t counter_order_date;     // 申报日期，格式为YYYYMMDD
    int32_t counter_order_time;     // 申报时间，格式为HHMMSSmmm
    int32_t counter_cancel_time;    // 撤销时间，格式为HHMMSSmmm
    int32_t exercise_status;        // 行权状态
    int32_t oper_status;            // 行权操作状态
    char symbol[LEN_SYMBOL];        // 交易标的，格式为市场.证券ID或市场.合约ID
    int32_t volume;                 // 成交数量
    int32_t cancel_volume;          // 交易所返回的撤单数量
    int32_t err_code;               // 行权失败时的错误码
    char err_msg[LEN_ERR_MSG];      // 行权失败时的错误消息，Windows是GBK，Linux是UTF8
};

// 期权合约信息
struct ContractInfo {
    char contract_id[LEN_SYMBOL];                   // 合约代码，格式为市场.证券ID或市场.合约ID
    char exch_contract_id[LEN_SYMBOL];              // 交易所合约代码
    char contract_name[LEN_SYMBOL_NAME];            // 合约名称
    char underlying_contract_id[LEN_SYMBOL];        // 基础证券代码
    char underlying_contract_name[LEN_SYMBOL_NAME]; // 基础证券名称
    int32_t underlying_multiplier;                  // 合约基础商品乘数
    int32_t strike_mode;                            // 执行方式，参考StrikeModeType定义
    int32_t options_type;                           // 期权类型，参考OptionsType定义
    int32_t order_unit;                             // 申报单位，参考OrderUnitType定义
    int32_t buy_trading_unit;                       // 买入交易单位
    int32_t sell_trading_unit;                      // 卖出交易单位
    int32_t max_market_order_buy_volume;            // 市价单买最大下单量
    int32_t min_market_order_buy_volume;            // 市价单买最小下单量
    int32_t max_limit_order_buy_volume;             // 限价单买最大下单量
    int32_t min_limit_order_buy_volume;             // 限价单买最小下单量
    int32_t max_market_order_sell_volume;           // 市价单卖最大下单量
    int32_t min_market_order_sell_volume;           // 市价单卖最小下单量
    int32_t max_limit_order_sell_volume;            // 限价单卖最大下单量
    int32_t min_limit_order_sell_volume;            // 限价单卖最小下单量
    int32_t volume_multiplier;                      // 数量乘数
    int64_t price_tick;                             // 最小变动价位，扩大一万倍
    int32_t contract_status;                        // 合约状态，参考ContractStatus定义
    int64_t strike_price;                           // 执行价，扩大一万倍
    int32_t first_date;                             // 首交易日
    int32_t last_date;                              // 最后交易日
    int32_t strike_date;                            // 行权日
    int32_t expire_date;                            // 到期日
    int32_t deliv_date;                             // 交割日
    int32_t is_up_down_limit;                       // 是否有涨跌幅限制，1表示是，0表示否
    int64_t margin_unit;                            // 期权单位保证金，扩大一万倍
    int64_t pre_settlement_price;                   // 合约前结算价，扩大一万倍
    int64_t pre_close_price;                        // 合约前收盘价，扩大一万倍
    int64_t underlying_pre_close_price;             // 标的合约前收盘价，扩大一万倍
};

// 现货持仓划转请求类型
struct TransferStockReq {
    char symbol[LEN_SYMBOL];    // 转移标的代码，格式为市场.证券ID或市场.合约ID
    int16_t transfer_type;      // 现货持仓转移类型，参考TransferPositionType定义
    int16_t transfer_side;      // 现货持仓转移方向，参考TransferStockPositionSide定义
    int64_t transfer_qty;       // 转移数量
};

// 现货持仓划转应答类型
struct TransferStockRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];    // 转移标的代码，格式为市场.证券ID或市场.合约ID
    int16_t transfer_type;      // 现货持仓转移类型，参考TransferPositionType定义
    int16_t transfer_side;      // 现货持仓转移方向，参考TransferStockPositionSide定义
    int64_t transfer_qty;       // 转移数量
};

// 现货持仓划转明细数据
struct TransferStockDetail {
    char account_id[LEN_ID];            // 交易账号，目前是资金账号
    int16_t account_type;               // 交易账号类型，参考AccountType定义
    char serial_number[LEN_ID];         // 转移流水号
    char symbol[LEN_SYMBOL];            // 转移标的代码，格式为市场.证券ID或市场.合约ID
    int32_t transact_date;              // 处理日期，格式为YYYYMMDD
    int32_t transact_time;              // 处理时间，格式为HHMMSSmmm
    int16_t transfer_type;              // 仓位转移类型，参考TransferPositionType定义
    int16_t transfer_side;              // 仓位转移方向，参考TransferStockPositionSide定义
    int16_t transfer_status;            // 转移状态，请参考TransferStatus定义
    int64_t yesterday_volume;           // 昨日仓位量
    int64_t today_bs_volume;            // 今日买卖仓位量
    int64_t today_pr_volume;            // 今日申赎仓位量
    char stock_cust_id[LEN_ID];         // 现货系统客户号
    char stock_secuid[LEN_ID];          // 现货系统股东代码
    char status_msg[LEN_ERR_MSG];       // 转移状态信息
};

// 锁定现货委托请求类型
struct LockOrderReq {
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，可不传
    char symbol[LEN_SYMBOL];    // 现货锁定标的，格式为市场.证券ID或市场.合约ID
    int16_t lock_type;          // 现货锁定类型，参考LockStockType定义
    int64_t volume;             // 现货锁定数量
};

// 锁定现货委托应答类型
struct LockOrderRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int16_t lock_type;          // 现货锁定类型，参考LockStockType定义
    char order_id[LEN_ID];      // 系统生成的锁定委托id
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，原样返回
};

// 锁定现货委托明细数据
struct LockOrderDetail {
    char account_id[LEN_ID];            // 交易账号
    int16_t account_type;               // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];            // 锁定的标的代码，格式为市场.证券ID或市场.合约ID
    char cl_order_id[LEN_ID];           // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];              // 柜台锁定委托编号
    int32_t order_date;                 // 申报日期，格式为YYYYMMDD
    int32_t order_time;                 // 申报时间，格式为HHMMSSmmm
    int32_t cancel_time;                // 撤销时间，格式为HHMMSSmmm
    int16_t lock_type;                  // 锁定类型，参考LockStockType定义
    int16_t lock_status;                // 锁定状态，成功、失败，参考LockStockStatus定义
    int64_t volume;                     // 委托数量
    int64_t cancel_volume;              // 撤销数量
    int32_t err_code;                   // 委托失败时的错误码
    char err_msg[LEN_ERR_MSG];          // 委托失败时的错误消息，Windows是GBK，Linux是UTF8
};

// 组合委托请求类型
struct CombOrderReq {
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，可不传
    char symbol[LEN_SYMBOL];    // 组合合约代码，格式为市场.合约ID&合约ID，例如SHOP.10002421&10002401
                                // 对于保证金开仓转备兑、备兑仓转普通，是单个合约代码
    int16_t comb_type;          // 组合报单类型，参考OptionCombineType定义
    int16_t comb_strategy;      // 组合策略类型，参考OptionCombineStrategy定义
    int64_t volume;             // 订单数量，单位：份
    char exch_comb_id[LEN_ID];  // 交易所组合编码（拆分组合时必填），组合委托推送状态为成交时返回
};

// 组合委托应答类型
struct CombOrderRsp {
    char account_id[LEN_ID];    // 交易账号，目前是资金账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int16_t comb_type;          // 组合报单类型，参考OptionCombineType定义
    char order_id[LEN_ID];      // 系统生成的组合委托id
    char cl_order_id[LEN_ID];   // 客户端订单id，用来引用一个普通订单，由用户自定义，原样返回
};

// 组合行权的请求类型
struct CombExerciseReq {
    char cl_order_id[LEN_ID];       // 客户端订单id，由用户自定义，用来引用一个普通订单
    char call_symbol[LEN_SYMBOL];   // 认购合约代码，格式为市场.合约ID，例如SHOP.10002421
    char put_symbol[LEN_SYMBOL];    // 认沽合约代码，格式为市场.合约ID，例如SHOP.10002401
    int64_t volume;                 // 数量
};

// 组合行权的响应类型
struct CombExerciseRsp {
    char account_id[LEN_ID];        // 交易账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char cl_order_id[LEN_ID];       // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];          // 柜台行权委托编号
};

// 撤销组合行权请求类型
struct CancelCombExerciseReq {
    char order_id[LEN_ID];          // 柜台行权委托编号
    char cl_order_id[LEN_ID];       // 客户端订单id，用来引用一个普通订单，由用户自定义，可不传
    char cl_cancel_id[LEN_ID];      // 客户端撤单id，用来引用一个撤单订单，由用户自定义，可不传
};

// 撤销组合行权响应类型
struct CancelCombExerciseRsp {
    char account_id[LEN_ID];        // 交易账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char order_id[LEN_ID];          // 柜台行权委托编号
    char cl_order_id[LEN_ID];       // 客户端订单id，用来引用一个普通订单，由用户自定义，原样返回
    char cl_cancel_id[LEN_ID];      // 客户端撤单id，用来引用一个撤单订单，由用户自定义，原样返回
};

// 组合委托明细数据
struct CombOrderDetail {
    char account_id[LEN_ID];            // 交易账号
    int16_t account_type;               // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];            // 组合合约代码，格式为市场.合约ID&合约ID，例如SHOP.10002421&10002401
    char exch_comb_id[LEN_ID];          // 交易所组合编码，拆分时使用
    int16_t comb_type;                  // 组合报单类型，参考OptionCombineType定义
    int16_t comb_strategy;              // 组合策略类型，参考OptionCombineStrategy定义
    char cl_order_id[LEN_ID];           // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];              // 柜台组合委托编号
    int32_t order_date;                 // 申报日期，格式为YYYYMMDD
    int32_t order_time;                 // 申报时间，格式为HHMMSSmmm
    int32_t cancel_time;                // 撤销时间，格式为HHMMSSmmm
    int16_t order_status;               // 组合委托状态，参考OrderStatus定义
    int16_t oper_status;                // 组合委托操作状态，参考ExerciseOperateStatus定义
    int64_t volume;                     // 委托数量
    int64_t cancel_volume;              // 撤销数量
    int32_t err_code;                   // 委托失败时的错误码
    char err_msg[LEN_ERR_MSG];          // 委托失败时的错误消息，Windows是GBK，Linux是UTF8
};

// 组合行权明细数据
struct CombExerciseDetail {
    char account_id[LEN_ID];        // 交易账号
    int16_t account_type;           // 交易账号类型，参考AccountType定义
    char call_symbol[LEN_SYMBOL];   // 认购合约代码，格式为市场.合约ID，例如SHOP.10002421
    char put_symbol[LEN_SYMBOL];    // 认沽合约代码，格式为市场.合约ID，例如SHOP.10002401
    char cl_order_id[LEN_ID];       // 客户端订单id，由用户自定义，用来引用一个普通订单
    char order_id[LEN_ID];          // 柜台组合行权委托编号
    int32_t order_date;             // 申报日期，格式为YYYYMMDD
    int32_t order_time;             // 申报时间，格式为HHMMSSmmm
    int32_t cancel_time;            // 撤销时间，格式为HHMMSSmmm
    int16_t exercise_status;        // 合并行权状态，参考ExerciseStatus定义
    int16_t oper_status;            // 行权操作状态，参考ExerciseOperateStatus定义
    int64_t volume;                 // 行权数量
    int64_t cancel_volume;          // 撤销数量
    int32_t err_code;               // 行权失败时的错误码
    char err_msg[LEN_ERR_MSG];      // 行权失败时的错误消息，Windows是GBK，Linux是UTF8
};

// 组合持仓明细数据
struct CombPositionDetail {
    char account_id[LEN_ID];            // 交易账号
    int16_t account_type;               // 交易账号类型，参考AccountType定义
    char symbol[LEN_SYMBOL];            // 组合合约代码，格式为市场.合约ID&合约ID，例如SHOP.10002421&10002401
    int16_t comb_strategy;              // 组合策略类型，参考OptionCombineStrategy定义
    int64_t volume;                     // 持仓总数量
    int64_t avail_volume;               // 持仓可用数量
    int64_t yesterday_volume;           // 昨日持仓量
    int64_t yesterday_avail_volume;     // 昨日可用持仓量
    int64_t today_volume;               // 今日买卖持仓量
    int64_t today_avail_volume;         // 今日买卖可用持仓量
    int64_t margin;                     // 占用的保证金，扩大一万倍
    int64_t frozen_margin;              // 冻结的保证金，扩大一万倍
    int64_t commission;                 // 手续费，扩大一万倍
    int64_t frozen_commission;          // 冻结的手续费，扩大一万倍
};

// 组合期权合约信息
struct CombContractInfo {
    char contract_id[LEN_SYMBOL];       // 组合合约代码，格式为市场.合约ID&合约ID，例如SHOP.10002421&10002401
    int16_t comb_strategy;              // 组合策略类型，参考OptionCombineStrategy定义
    char leg1_contract_id[LEN_SYMBOL];  // 成分一合约代码，格式为市场.证券ID或市场.合约ID
    char leg1_name[LEN_SYMBOL_NAME];    // 成分一合约名称
    int16_t leg1_side;                  // 策略要求的成分一合约多空方向，参考PositionSide定义
    char leg2_contract_id[LEN_SYMBOL];  // 成分二合约代码，格式为市场.证券ID或市场.合约ID
    char leg2_name[LEN_SYMBOL_NAME];    // 成分二合约名称
    int16_t leg2_side;                  // 策略要求的成分二合约多空方向，参考PositionSide定义
};

// 锁券明细
struct LockSecurityDetail {
    char account_id[LEN_ID];    // 交易账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    int32_t sys_date;           // 系统日期
    char sno[LEN_ID];           // 锁券流水号
    char symbol[LEN_SYMBOL];    // 标的代码，格式为市场.证券ID
    char name[LEN_SYMBOL_NAME]; // 证券名称
    int16_t lock_type;          // 收费模式
    int64_t used_fee_rate;      // 融券费率
    int64_t unused_fee_rate;    // 管理费率
    int32_t lock_qty;           // 锁券数量
    int32_t used_qty;           // 已使用数量
    int32_t back_qty;           // 回收数量
    int32_t begin_date;         // 开始日期
    int32_t back_date;          // 归还日期
    int32_t end_date;           // 结束日期
};

// 锁券展期申请请求
struct ExtendLockSecurityReq {
    int32_t sys_date;               // 锁券日期
    char sno[LEN_ID];               // 锁券流水号
    int32_t apply_delay_days;       // 申请展期天数
    int64_t apply_used_fee_rate;    // 申请使用费率
    int64_t apply_unused_fee_rate;  // 申请占用费率
    int32_t apply_delay_qty;        // 申请展期数量
    char symbol[LEN_SYMBOL];        // 标的代码，格式为市场.证券ID，顶点两融必送
};

struct LockSecurityExtensionDetail {
    char account_id[LEN_ID];            // 交易账号
    int16_t account_type;               // 交易账号类型，参考AccountType定义
    int32_t apply_date;                 // 申请日期
    int32_t apply_sno;                  // 申请流水号
    int32_t sys_date;                   // 起始日（系统日期)
    char sno[LEN_ID];                   // 流水号
    char symbol[LEN_SYMBOL];            // 锁定的标的代码，格式为市场.证券ID
    char name[LEN_ID];                  // 证券名称
    int32_t apply_end_date;             // 申请展期到期日
    int32_t apply_delay_qty;            // 申请展期股数
    int64_t approval_used_fee_rate;     // 审批融券费率
    int64_t approval_unused_fee_rate;   // 审批管理费率
    int16_t approval_status;            // 审批状态，参见ApprovalStatus定义
    char approval_remark[LEN_ERR_MSG];  // 审批批注
};

// 资金划转流水明细数据
struct TransferFundDetail {
    char account_id[LEN_ID];    // 交易账号
    int16_t account_type;       // 交易账号类型，参考AccountType定义
    char serial_number[LEN_ID]; // 转移流水号
    int32_t transact_date;      // 处理日期YYYYMMDD
    int32_t transact_time;      // 处理时间HHMMSSmmm
    int64_t transfer_value;     // 转移金额，扩大1万倍
    int16_t transfer_side;      // 转入/转出，请参考TransferFundSide
    int16_t transfer_status;    // 转移状态，请参考TransferStatus
    char remark[LEN_ERR_MSG];   // 备注
};

}  // namespace HFT

#endif  // _HFT_TRADER_STRUCT_H_
