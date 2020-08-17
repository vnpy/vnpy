//=============================================================================
/* 新易盛统一交易API接口
 * 该文件定义了EsTradeAPI 使用的数据类型
 * 版本信息:2018-05-21 郭晓刚 创建该文件
 */
//=============================================================================
#ifndef ES_TRADE_API_DATA_TYPE_H
#define ES_TRADE_API_DATA_TYPE_H
namespace EsTradeAPI
{
#pragma pack(push, 1)

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_CHARS    基本字符串类型定义
     *    @{
     */
     //=============================================================================
     //! 单字符定义，可用于定义其他类型
    typedef char        TAPICHAR;
    //! 长度为10的字符串
    typedef char        TAPISTR_10[11];
    //! 长度为20的字符串
    typedef char        TAPISTR_20[21];
    //! 长度为30的字符串
    typedef char        TAPISTR_30[31];
    //! 长度为40的字符串
    typedef char        TAPISTR_40[41];
    //! 长度为50的字符串
    typedef char        TAPISTR_50[51];
    //! 长度为70的字符串
    typedef char        TAPISTR_70[71];
    //! 长度为100的字符串
    typedef char        TAPISTR_100[101];
    //! 长度为200的字符串
    typedef char        TAPISTR_200[201];
    //! 长度为300的字符串
    typedef char        TAPISTR_300[301];
    //! 长度为500的字符串
    typedef char        TAPISTR_500[501];
    //! 长度为2000的字符串
    typedef char        TAPISTR_2000[2001];
    //! 长度为512的认证码字符串Authorization Code
    typedef char        TAPIAUTHCODE[513];
    //! 二次认证序号
    typedef char                    TAPISecondSerialIDType[5];

    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_NUMBER    基本数值类型定义
     *    @{
     */
     //=============================================================================
     //! int 32
    typedef int        TAPIINT32;
    //! unsigned 32
    typedef unsigned int    TAPIUINT32;
    //! int 64
    typedef long long    TAPIINT64;
    //! unsigned 64
    typedef unsigned long long    TAPIUINT64;
    //! unsigned 16
    typedef unsigned short    TAPIUINT16;
    //! unsigned 8
    typedef unsigned char    TAPIUINT8;
    //! real 64
    typedef double        TAPIREAL64;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_YNFLAG    是否标示
     *    @{
     */
     //=============================================================================
     //! 是否标示
    typedef TAPICHAR    TAPIYNFLAG;
    //! 是
    const TAPIYNFLAG    APIYNFLAG_YES = 'Y';
    //! 否
    const TAPIYNFLAG    APIYNFLAG_NO = 'N';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_DATETIME    日期时间类型定义
     *    @{
     */
     //=============================================================================
     //! 时间戳类型(格式 yyyy-MM-dd hh:nn:ss.xxx)
    typedef char        TAPIDTSTAMP[24];
    //! 日期和时间类型(格式 yyyy-MM-dd hh:nn:ss)
    typedef char        TAPIDATETIME[20];
    //! 日期类型(格式 yyyy-MM-dd)
    typedef char        TAPIDATE[11];
    //! 时间类型(格式 hh:nn:ss)
    typedef char        TAPITIME[9];
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_LOG_LEVEL    日志级别
     *    @{
     */
     //=============================================================================
     //! 日志级别
    typedef TAPICHAR    TAPILOGLEVEL;
    //! Error
    const TAPILOGLEVEL    APILOGLEVEL_ERROR = '1';
    //! Normal
    const TAPILOGLEVEL    APILOGLEVEL_NORMAL = '2';
    //! Debug
    const TAPILOGLEVEL    APILOGLEVEL_DEBUG = '3';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_COMMODITY_TYPE    品种类型
     *    @{
     */
     //=============================================================================
     //! 品种类型
    typedef TAPICHAR    TAPICommodityType;
    //! 无
    const TAPICommodityType     TAPI_COMMODITY_TYPE_NONE = 'N';
    //! 现货
    const TAPICommodityType    TAPI_COMMODITY_TYPE_SPOT = 'P';
    //! 期货
    const TAPICommodityType    TAPI_COMMODITY_TYPE_FUTURES = 'F';
    //! 期权
    const TAPICommodityType    TAPI_COMMODITY_TYPE_OPTION = 'O';
    //! 跨期套利
    const TAPICommodityType    TAPI_COMMODITY_TYPE_SPREAD_MONTH = 'S';
    //! 跨品种套利
    const TAPICommodityType    TAPI_COMMODITY_TYPE_SPREAD_COMMODITY = 'M';
    //! 看涨垂直套利
    const TAPICommodityType    TAPI_COMMODITY_TYPE_BUL = 'U';
    //! 看跌垂直套利
    const TAPICommodityType    TAPI_COMMODITY_TYPE_BER = 'E';
    //! 跨式套利
    const TAPICommodityType    TAPI_COMMODITY_TYPE_STD = 'D';
    //! 宽跨式套利
    const TAPICommodityType    TAPI_COMMODITY_TYPE_STG = 'G';
    //! 备兑组合
    const TAPICommodityType    TAPI_COMMODITY_TYPE_PRT = 'R';
    //! 看涨水平期权
    const TAPICommodityType        TAPI_COMMODITY_TYPE_BLT = 'L';
    //! 看跌水平期权
    const TAPICommodityType       TAPI_COMMODITY_TYPE_BRT = 'Q';
    //! 外汇——直接汇率
    const TAPICommodityType    TAPI_COMMODITY_TYPE_DIRECTFOREX = 'X';
    //! 外汇——间接汇率
    const TAPICommodityType    TAPI_COMMODITY_TYPE_INDIRECTFOREX = 'I';
    //! 外汇——交叉汇率
    const TAPICommodityType    TAPI_COMMODITY_TYPE_CROSSFOREX = 'C';
    //! 指数
    const TAPICommodityType    TAPI_COMMODITY_TYPE_INDEX = 'Z';
    //! 股票
    const TAPICommodityType    TAPI_COMMODITY_TYPE_STOCK = 'T';
    //! 现货延期
    const TAPICommodityType    TAPI_COMMODITY_TYPE_SPOT_TRADINGDEFER = 'Y';
    //! 对锁组合
    const TAPICommodityType            TAPI_COMMODITY_TYPE_FUTURE_LOCK = 'J';
    //! 中金所EFP
    const TAPICommodityType        TAPI_COMMODITY_TYPE_EFP = 'A';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_CALL_OR_PUT    看涨看跌标示
     *    @{
     */
     //=============================================================================
     //! 看涨看跌标示
    typedef TAPICHAR    TAPICallOrPutFlagType;
    //! 买权
    const TAPICallOrPutFlagType    TAPI_CALLPUT_FLAG_CALL = 'C';
    //! 卖权
    const TAPICallOrPutFlagType    TAPI_CALLPUT_FLAG_PUT = 'P';
    //! 无
    const TAPICallOrPutFlagType    TAPI_CALLPUT_FLAG_NONE = 'N';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIACCOUNTTYPE    账号类型
     *    @{
     */
     //=============================================================================
     //! 账号类型
    typedef TAPICHAR    TAPIAccountType;
    //! 个人客户
    const TAPIAccountType    TAPI_ACCOUNT_TYPE_PERSON = 'P';
    //! 机构客户
    const TAPIAccountType    TAPI_ACCOUNT_TYPE_ORGANIZATION = 'O';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIRIGHTIDTYPE    权限编码类型
    *    @{
    */
    //=============================================================================
    //! 权限编码类型
    typedef TAPIINT32    TAPIRightIDType;
    //! 系统删单
    const TAPIRightIDType    TAPI_RIGHT_ORDER_DEL = 30001;
    //! 订单审核
    const TAPIRightIDType    TAPI_RIGHT_ORDER_CHECK = 30002;
    //! 只可查询
    const TAPIRightIDType    TAPI_RIGHT_ONLY_QRY = 31000;
    //! 只可开仓
    const TAPIRightIDType    TAPI_RIGHT_ONLY_OPEN = 31001;
    //! 上期查挂单
    const TAPIRightIDType    TAPI_RIGHT_SHFE_QUOTE = 31002;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIUSERTYPETYPE    登录用户身份类型
     *    @{
     */
     //=============================================================================
     //! 登录用户身份类型
    typedef TAPIINT32    TAPIUserTypeType;
    //! 投资者用户
    const TAPIUserTypeType    TAPI_USERTYPE_CLIENT = 10000;
    //! 经纪人
    const TAPIUserTypeType    TAPI_USERTYPE_BROKER = 20000;
    //! 交易员
    const TAPIUserTypeType    TAPI_USERTYPE_TRADER = 30000;
    //! 风控
    const TAPIUserTypeType    TAPI_USERTYPE_RISK = 40000;
    //! 管理员
    const TAPIUserTypeType    TAPI_USERTYPE_MANAGER = 50000;
    //! 行情
    const TAPIUserTypeType    TAPI_USERTYPE_QUOTE = 60000;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIACCOUNTSTATE    账号状态
     *    @{
     */
     //=============================================================================
     //! 账号状态
    typedef TAPICHAR    TAPIAccountState;
    //! 正常
    const TAPIAccountState    TAPI_ACCOUNT_STATE_NORMAL = 'N';
    //! 销户
    const TAPIAccountState    TAPI_ACCOUNT_STATE_CANCEL = 'C';
    //! 休眠
    const TAPIAccountState    TAPI_ACCOUNT_STATE_SLEEP = 'S';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIACCOUNTFAMILYTYPE    父子账户类型
     *    @{
     */
     //=============================================================================
     //! 父子账户类型
    typedef TAPICHAR    TAPIAccountFamilyType;
    //! 正常账号
    const    TAPIAccountFamilyType    TAPI_ACCOUNT_FAMILYTYPE_NOMAL = 'N';
    //! 子账户
    const    TAPIAccountFamilyType    TAPI_ACCOUNT_FAMILYTYPE_CHILD = 'C';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERTYPETYPE    委托类型
     *    @{
     */
     //=============================================================================
     //! 委托类型
    typedef TAPICHAR    TAPIOrderTypeType;
    //! 市价
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_MARKET = '1';
    //! 限价
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_LIMIT = '2';
    //! 市价止损
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_STOP_MARKET = '3';
    //! 限价止损
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_STOP_LIMIT = '4';
    //! 期权行权
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_OPT_EXEC = '5';
    //! 期权弃权
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_OPT_ABANDON = '6';
    //! 询价
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_REQQUOT = '7';
    //! 应价
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_RSPQUOT = '8';
    //! 互换
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_SWAP = '9';
    //! 组合申请
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_COMB = 'A';
    //! 拆分申请
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_UNCOMB = 'B';
    //! 市价止盈
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_PROFIT_MARKET = 'C';
    //! 限价止盈
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_PROFIT_LIMIT = 'D';
    //! 套保申请
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_HEDGE = 'E';
    //! 期权自对冲
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_OPTION_AUTO_CLOSE = 'F';
    //! 履约期货自对冲
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_FUTURE_AUTO_CLOSE = 'G';
    //! 做市商留仓申请
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_MARKET_POSITION_KEEP = 'H';
    //! 大商所取消到日期自动行权
    const TAPIOrderTypeType    TAPI_ORDER_TYPE_OPTION_AUTOEXEC_ABAND = 'I';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERSOURCETYPE    委托来源
     *    @{
     */
     //=============================================================================
     //! 委托来源
    typedef TAPICHAR    TAPIOrderSourceType;
    //! 自助电子单
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_SELF_ETRADER = '1';
    //! 代理电子单
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_PROXY_ETRADER = '2';
    //! 外部电子单(外部电子系统下单，本系统录入)
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_JTRADER = '3';
    //! 人工录入单(外部其他方式下单，本系统录入)
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_MANUAL = '4';
    //! carry单
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_CARRY = '5';
    //! 程式化报单
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_PROGRAM = '6';
    //! 交割行权
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_DELIVERY = '7';
    //! 期权放弃
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_ABANDON = '8';
    //! 通道费
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_CHANNEL = '9';
    //! 易盛API
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_ESUNNY_API = 'A';
    //! 易盛V8客户端
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_ESV8CLIENT = 'B';
    //! 易盛极星客户端
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_EPOLESTAR = 'C';
    //! 易盛易星客户端
    const TAPIOrderSourceType    TAPI_ORDER_SOURCE_ESTAR = 'D';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITIMEINFORCETYPE    委托有效类型
     *    @{
     */
     //=============================================================================
     //! 委托有效类型
    typedef TAPICHAR    TAPITimeInForceType;
    //! 当日有效(手机仿真只支持该类型)
    const TAPITimeInForceType    TAPI_ORDER_TIMEINFORCE_GFD = '0';
    //! 取消前有效
    const TAPITimeInForceType    TAPI_ORDER_TIMEINFORCE_GTC = '1';
    //! 指定日期前有效
    const TAPITimeInForceType    TAPI_ORDER_TIMEINFORCE_GTD = '2';
    //! FAK或IOC
    const TAPITimeInForceType    TAPI_ORDER_TIMEINFORCE_FAK = '3';
    //! FOK
    const TAPITimeInForceType    TAPI_ORDER_TIMEINFORCE_FOK = '4';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPISIDETYPE    买卖类型
     *    @{
     */
     //=============================================================================
     //! 买卖类型
    typedef TAPICHAR    TAPISideType;
    //! 无
    const TAPISideType    TAPI_SIDE_NONE = 'N';
    //! 买入
    const TAPISideType    TAPI_SIDE_BUY = 'B';
    //! 卖出
    const TAPISideType    TAPI_SIDE_SELL = 'S';
    //! 双边
    const TAPISideType    TAPI_SIDE_ALL = 'A';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIPOSITIONEFFECTTYPE    开平类型
     *    @{
     */
     //=============================================================================
     //! 开平类型
    typedef TAPICHAR    TAPIPositionEffectType;
    //! 不分开平
    const TAPIPositionEffectType    TAPI_PositionEffect_NONE = 'N';
    //! 开仓
    const TAPIPositionEffectType    TAPI_PositionEffect_OPEN = 'O';
    //! 平仓
    const TAPIPositionEffectType    TAPI_PositionEffect_COVER = 'C';
    //! 平当日
    const TAPIPositionEffectType    TAPI_PositionEffect_COVER_TODAY = 'T';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIHEDGEFLAGTYPE    投机保值类型
     *    @{
     */
     //=============================================================================
     //! 投机保值类型
    typedef TAPICHAR    TAPIHedgeFlagType;
    //! 无
    const TAPIHedgeFlagType    TAPI_HEDGEFLAG_NONE = 'N';
    //! 投机
    const TAPIHedgeFlagType    TAPI_HEDGEFLAG_T = 'T';
    //! 保值
    const TAPIHedgeFlagType    TAPI_HEDGEFLAG_B = 'B';
    //! 套利
    const TAPIHedgeFlagType    TAPI_HEDGEFLAG_L = 'L';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERSTATETYPE    委托状态类型
     *    @{
     */
     //=============================================================================
     //! 委托状态类型
    typedef TAPICHAR    TAPIOrderStateType;
    //! 终端提交
    const TAPIOrderStateType    TAPI_ORDER_STATE_SUBMIT = '0';
    //! 已受理
    const TAPIOrderStateType    TAPI_ORDER_STATE_ACCEPT = '1';
    //! 策略待触发
    const TAPIOrderStateType    TAPI_ORDER_STATE_TRIGGERING = '2';
    //! 交易所待触发
    const TAPIOrderStateType    TAPI_ORDER_STATE_EXCTRIGGERING = '3';
    //! 已排队
    const TAPIOrderStateType    TAPI_ORDER_STATE_QUEUED = '4';
    //! 部分成交
    const TAPIOrderStateType    TAPI_ORDER_STATE_PARTFINISHED = '5';
    //! 完全成交
    const TAPIOrderStateType    TAPI_ORDER_STATE_FINISHED = '6';
    //! 待撤消(排队临时状态)
    const TAPIOrderStateType    TAPI_ORDER_STATE_CANCELING = '7';
    //! 待修改(排队临时状态)
    const TAPIOrderStateType    TAPI_ORDER_STATE_MODIFYING = '8';
    //! 完全撤单
    const TAPIOrderStateType    TAPI_ORDER_STATE_CANCELED = '9';
    //! 已撤余单
    const TAPIOrderStateType    TAPI_ORDER_STATE_LEFTCANCELED = 'A';
    //! 指令失败
    const TAPIOrderStateType    TAPI_ORDER_STATE_FAIL = 'B';
    //! 策略删除
    const TAPIOrderStateType    TAPI_ORDER_STATE_DELETED = 'C';
    //! 已挂起
    const TAPIOrderStateType    TAPI_ORDER_STATE_SUPPENDED = 'D';
    //! 到期删除
    const TAPIOrderStateType    TAPI_ORDER_STATE_DELETEDFOREXPIRE = 'E';
    //! 已生效——询价成功
    const TAPIOrderStateType    TAPI_ORDER_STATE_EFFECT = 'F';
    //! 已申请——行权、弃权、套利等申请成功
    const TAPIOrderStateType    TAPI_ORDER_STATE_APPLY = 'G';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPICALCULATEMODETYPE    计算方式
     *    @{
     */
     //=============================================================================
     //! 计算方式
    typedef TAPICHAR    TAPICalculateModeType;
    //! 比例
    const TAPICalculateModeType    TAPI_CALCULATE_MODE_PERCENTAGE = '1';
    //! 定额
    const TAPICalculateModeType    TAPI_CALCULATE_MODE_QUOTA = '2';
    //! 绝对方式
    const TAPICalculateModeType    TAPI_CALCULATE_MODE_ABSOLUTE = '7';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIMATCHSOURCETYPE    成交来源
     *    @{
     */
     //=============================================================================
     //! 成交来源
    typedef TAPICHAR    TAPIMatchSourceType;
    //! 全部
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_ALL = '0';
    //! 自助电子单
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_SELF_ETRADER = '1';
    //! 代理电子单
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_PROXY_ETRADER = '2';
    //! 外部电子单
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_JTRADER = '3';
    //! 人工录入单
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_MANUAL = '4';
    //! carry单
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_CARRY = '5';
    //! 程式化单
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_PROGRAM = '6';
    //! 交割行权
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_DELIVERY = '7';
    //! 期权放弃
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_ABANDON = '8';
    //! 通道费
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_CHANNEL = '9';
    //! 易盛API
    const TAPIMatchSourceType    TAPI_MATCH_SOURCE_ESUNNY_API = 'A';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIOPENCLOSEMODETYPE    开平方式
     *    @{
     */
     //=============================================================================
     //! 开平方式
    typedef TAPICHAR    TAPIOpenCloseModeType;
    //! 不区分开平
    const TAPIOpenCloseModeType    TAPI_CLOSE_MODE_NONE = 'N';
    //! 平仓未了结
    const TAPIOpenCloseModeType    TAPI_CLOSE_MODE_UNFINISHED = 'U';
    //! 区分开仓和平仓
    const TAPIOpenCloseModeType    TAPI_CLOSE_MODE_OPENCOVER = 'C';
    //! 区分开仓、平仓和平今
    const TAPIOpenCloseModeType    TAPI_CLOSE_MODE_CLOSETODAY = 'T';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIFUTUREALGTYPE    期货算法
     *    @{
     */
     //=============================================================================
     //! 期货算法
    typedef TAPICHAR    TAPIFutureAlgType;
    //! 逐笔
    const TAPIFutureAlgType    TAPI_FUTURES_ALG_ZHUBI = '1';
    //! 盯市
    const TAPIFutureAlgType    TAPI_FUTURES_ALG_DINGSHI = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIOPTIONALGTYPE    期权算法
     *    @{
     */
     //=============================================================================
     //! 期权算法
    typedef TAPICHAR    TAPIOptionAlgType;
    //! 期货方式
    const TAPIOptionAlgType    TAPI_OPTION_ALG_FUTURES = '1';
    //! 期权方式
    const TAPIOptionAlgType    TAPI_OPTION_ALG_OPTION = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIBANKACCOUNTLWFLAGTYPE    本外币标识
     *    @{
     */
     //=============================================================================
     //! 本外币标识
    typedef TAPICHAR    TAPIBankAccountLWFlagType;
    //! 境内人民币账户
    const TAPIBankAccountLWFlagType    TAPI_LWFlag_L = 'L';
    //! 客户境内外币账户
    const TAPIBankAccountLWFlagType    TAPI_LWFlag_W = 'W';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIMARGINCALCULATEMODETYPE    期货保证金方式
     *    @{
     */
     //=============================================================================
     //! 期货保证金方式
    typedef TAPICHAR    TAPIMarginCalculateModeType;
    //! 分笔
    const TAPIMarginCalculateModeType    TAPI_DEPOSITCALCULATE_MODE_FEN = '1';
    //! 锁仓
    const TAPIMarginCalculateModeType    TAPI_DEPOSITCALCULATE_MODE_SUO = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIOPTIONMARGINCALCULATEMODETYPE    期权保证金公式
     *    @{
     */
     //=============================================================================
     //! 期权保证金公式,据此判断该品种期权采用何种内置计算公式计算保证金
    typedef TAPICHAR    TAPIOptionMarginCalculateModeType;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPICMBDIRECTTYPE    组合方向
     *    @{
     */
     //=============================================================================
     //! 组合方向,品种两腿组合合约的买卖方向和第几腿相同
    typedef TAPICHAR    TAPICmbDirectType;
    //! 和第一腿一致
    const TAPICmbDirectType         TAPI_CMB_DIRECT_FIRST = '1';
    //! 和第二腿一致
    const TAPICmbDirectType         TAPI_CMB_DIRECT_SECOND = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIDELIVERYMODETYPE    交割行权方式
     *    @{
     */
     //=============================================================================
     //! 交割行权方式,期货和期权了结的方式
    typedef TAPICHAR    TAPIDeliveryModeType;
    //! 实物交割
    const TAPIDeliveryModeType    TAPI_DELIVERY_MODE_GOODS = 'G';
    //! 现金交割
    const TAPIDeliveryModeType    TAPI_DELIVERY_MODE_CASH = 'C';
    //! 期权行权
    const TAPIDeliveryModeType    TAPI_DELIVERY_MODE_EXECUTE = 'E';
    //! 期权放弃
    const TAPIDeliveryModeType    TAPI_DELIVERY_MODE_ABANDON = 'A';
    //! 港交所行权
    const TAPIDeliveryModeType    TAPI_DELIVERY_MODE_HKF = 'H';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPICONTRACTTYPETYPE    合约类型
     *    @{
     */
     //=============================================================================
     //! 合约类型
    typedef TAPICHAR    TAPIContractTypeType;
    //! 交易行情合约
    const TAPIContractTypeType    TAPI_CONTRACT_TYPE_TRADEQUOTE = '1';
    //! 行情合约
    const TAPIContractTypeType    TAPI_CONTRACT_TYPE_QUOTE = '2';
    /** @}*/

    //=============================================================================
    //T+1成交
    typedef TAPICHAR    TAPIIsAddOneType;
    //T+1成交
    const TAPIIsAddOneType    TAPI_ISADD_ONE_YES = 'Y';
    //非T+1成交
    const TAPIIsAddOneType    TAPI_ISADD_ONE_NO = 'N';

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITACTICSTYPETYPE    策略单类型
     *    @{
     */
     //=============================================================================
     //! 策略单类型
    typedef TAPICHAR    TAPITacticsTypeType;
    //! 无
    const TAPITacticsTypeType    TAPI_TACTICS_TYPE_NONE = 'N';
    //! 预备单(埋单)
    const TAPITacticsTypeType    TAPI_TACTICS_TYPE_READY = 'M';
    //! 自动单
    const TAPITacticsTypeType    TAPI_TACTICS_TYPE_ATUO = 'A';
    //! 条件单
    const TAPITacticsTypeType    TAPI_TACTICS_TYPE_CONDITION = 'C';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERACT    订单操作类型
     *    @{
     */
     //=============================================================================
     //! 订单操作类型
    typedef TAPICHAR    TAPIORDERACT;
    //! 报单
    const TAPIORDERACT    APIORDER_INSERT = '1';
    //! 改单
    const TAPIORDERACT    APIORDER_MODIFY = '2';
    //! 撤单
    const TAPIORDERACT    APIORDER_DELETE = '3';
    //! 挂起
    const TAPIORDERACT    APIORDER_SUSPEND = '4';
    //! 激活
    const TAPIORDERACT    APIORDER_ACTIVATE = '5';
    //! 删除
    const TAPIORDERACT    APIORDER_SYSTEM_DELETE = '6';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITRIGGERCONDITIONTYPE    触发条件类型
     *    @{
     */
     //=============================================================================
     //! 触发条件类型
    typedef TAPICHAR    TAPITriggerConditionType;
    //! 无
    const TAPITriggerConditionType    TAPI_TRIGGER_CONDITION_NONE = 'N';
    //! 大于等于
    const TAPITriggerConditionType    TAPI_TRIGGER_CONDITION_GREAT = 'G';
    //! 小于等于
    const TAPITriggerConditionType    TAPI_TRIGGER_CONDITION_LITTLE = 'L';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITRIGGERPRICETYPETYPE    触发价格类型
     *    @{
     */
     //=============================================================================
     //! 触发价格类型
    typedef TAPICHAR    TAPITriggerPriceTypeType;
    //! 无
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_NONE = 'N';
    //! 买价
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_BUY = 'B';
    //! 卖价
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_SELL = 'S';
    //! 最新价
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_LAST = 'L';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIMARKETLEVELTYPE    市价撮合深度
     *    @{
     */
     //=============================================================================
     //! 市价撮合深度
    typedef TAPIUINT8    TAPIMarketLevelType;
    //! 任意价
    const TAPIMarketLevelType    TAPI_MARKET_LEVEL_0 = 0;
    //! 1档最优价
    const TAPIMarketLevelType    TAPI_MARKET_LEVEL_1 = 1;
    //! 5档
    const TAPIMarketLevelType    TAPI_MARKET_LEVEL_5 = 5;
    //! 10档
    const TAPIMarketLevelType    TAPI_MARKET_LEVEL_10 = 10;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITRADINGSTATETYPE    交易状态
     *    @{
     */
     //=============================================================================
     //! 交易状态
    typedef TAPICHAR    TAPITradingStateType;
    //! 集合竞价
    const TAPITradingStateType    TAPI_TRADE_STATE_BID = '1';
    //! 集合竞价撮合
    const TAPITradingStateType    TAPI_TRADE_STATE_MATCH = '2';
    //! 连续交易
    const TAPITradingStateType    TAPI_TRADE_STATE_CONTINUOUS = '3';
    //! 交易暂停
    const TAPITradingStateType    TAPI_TRADE_STATE_PAUSED = '4';
    //! 闭市
    const TAPITradingStateType    TAPI_TRADE_STATE_CLOSE = '5';
    //! 闭市处理时间
    const TAPITradingStateType    TAPI_TRADE_STATE_DEALLAST = '6';
    //! 网关未连
    const TAPITradingStateType    TAPI_TRADE_STATE_GWDISCONNECT = '0';
    //! 未知状态
    const TAPITradingStateType    TAPI_TRADE_STATE_UNKNOWN = 'N';
    //! 正初始化
    const TAPITradingStateType    TAPI_TRADE_STATE_INITIALIZE = 'I';
    //! 准备就绪
    const TAPITradingStateType    TAPI_TRADE_STATE_READY = 'R';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPINOTICEIGNOREFLAGTYPE    忽略后台推送通知标记
     *    @{
     */
     //=============================================================================
     //! 忽略后台推送通知标记
    typedef TAPIUINT32    TAPINoticeIgnoreFlagType;
    //! 推送所有信息
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_NONE = 0x00000000;
    //! 忽略所有推送
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_ALL = 0xFFFFFFFF;
    //! 忽略资金推送:OnRtnFund
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_FUND = 0x00000001;
    //! 忽略委托推送:OnRtnOrder
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_ORDER = 0x00000002;
    //! 忽略成交推送:OnRtnFill
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_FILL = 0x00000004;
    //! 忽略持仓推送:OnRtnPosition
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_POSITION = 0x00000008;
    //! 忽略平仓推送:OnRtnClose
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_CLOSE = 0x00000010;
    //! 忽略持仓盈亏推送:OnRtnPositionProfit
    const TAPINoticeIgnoreFlagType    TAPI_NOTICE_IGNORE_POSITIONPROFIT = 0x00000020;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERQRYTYPETYPE    委托查询类型
     *    @{
     */
     //=============================================================================
     //! 委托查询类型
    typedef TAPICHAR    TAPIOrderQryTypeType;
    //! 返回所有委托
    const TAPIOrderQryTypeType    TAPI_ORDER_QRY_TYPE_ALL = 'A';
    //! 只返回未结束的委托
    const TAPIOrderQryTypeType    TAPI_ORDER_QRY_TYPE_UNENDED = 'U';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPISystemTypeTypeE    后台系统类型
     *    @{
     */
     //=============================================================================
     //! 后台系统类型
    typedef TAPIUINT32    TAPISystemTypeType;
    //! 内盘启明星系统
    const TAPISystemTypeType    TAPI_SYSTEM_TYPE_ESUNNY = 1;
    //! 外盘北斗星系统
    const TAPISystemTypeType    TAPI_SYSTEM_TYPE_IESUNNY = 2;
    //! 手机后台系统
    const TAPISystemTypeType    TAPI_SYSTEM_TYPE_CELLPHONE = 3;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_LOGINTPYE    登录类型
     *    @{
     */
     //=============================================================================
     //! 登录类型
    typedef TAPIUINT32    TAPILoginTypeType;
    //! 普通TCP
    const TAPILoginTypeType    TAPI_LOGINTYPE_NORMAL = 1;
    //! 国密TCP(暂不支持)
    const TAPILoginTypeType    TAPI_LOGINTYPE_GMSSL = 2;
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIMSGLEVELTYPE    消息级别
    *    @{
    */
    //=============================================================================
    //! 消息级别
    typedef TAPICHAR    TAPIMsgLevelType;
    //! 普通
    const TAPIMsgLevelType    TAPI_MSG_LEVEL_NORMAL = '1';
    //! 重要
    const TAPIMsgLevelType    TAPI_MSG_LEVEL_IMPORTANT = '2';
    //! 紧急
    const TAPIMsgLevelType    TAPI_MSG_LEVEL_IMERGENCY = '3';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIMSGTYPETYPE    消息类型
    *    @{
    */
    //=============================================================================
    //! 消息类型
    typedef TAPICHAR    TAPIMsgTypeType;
    //! 管理
    const TAPIMsgTypeType    TAPI_Msg_TYPE_MANAGER = '1';
    //! 风险
    const TAPIMsgTypeType    TAPI_Msg_TYPE_RISKCONTROL = '2';
    /** @}*/
    
    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIMSGQRYTYPETYPE    消息类型查询类型
    *    @{
    */
    //=============================================================================
    //! 消息查询类型(北斗星专用，启明星后台默认全部)
    typedef TAPICHAR    TAPIMsgQryTypeType;
    //! 全部
    const TAPIMsgQryTypeType        TAPI_Msg_QRYTYPE_ALL = 'A';
    //! 有效
    const TAPIMsgQryTypeType        TAPI_Msg_QRYTYPE_VALID = 'Y';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPICASHADJUSTTYPETYPE    资金调整类型
    *    @{
    */
    //=============================================================================
    //! 资金调整类型
    typedef TAPICHAR        TAPICashAdjustTypeType;
    //! 手续费调整
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_FEEADJUST = '0';
    //! 盈亏调整
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_YKADJUST = '1';
    //! 质押资金
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_PLEDGE = '2';
    //! 利息收入
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_INTERESTREVENUE = '3';
    //! 代扣费用
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_COLLECTIONCOST = '4';
    //! 其它
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_OTHER = '5';
    //! 公司间拨账
    const TAPICashAdjustTypeType    TAPI_CASHINOUT_MODE_COMPANY = '6';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIBILLTYPETYPE    账单类型
    *    @{
    */
    //=============================================================================
    //! 账单类型
    typedef TAPICHAR    TAPIBillTypeType;
    //! 日账单
    const TAPIBillTypeType    TAPI_BILL_DATE = 'D';
    //! 月账单
    const TAPIBillTypeType    TAPI_BILL_MONTH = 'M';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIBILLFILETYPETYPE    帐单文件类型
    *    @{
    */
    //=============================================================================
    //! 帐单文件类型
    typedef TAPICHAR    TAPIBillFileTypeType;
    //! txt格式文件
    const TAPIBillFileTypeType    TAPI_BILL_FILE_TXT = 'T';
    //! pdf格式文件
    const TAPIBillFileTypeType    TAPI_BILL_FILE_PDF = 'F';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIAUTHTYPETYPE    授权登录文件类型
    *    @{
    */
    //=============================================================================
    //! 授权登录文件类型
    typedef TAPICHAR    TAPIAuthTypeType;
    //! 直连模式
    const TAPIAuthTypeType    TAPI_AUTHTYPE_DIRECT = '1';
    //! 中继模式
    const TAPIAuthTypeType    TAPI_AUTHTYPE_RELAY = '2';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPISENDTYPETYPE    二次认证发送方式
    *    @{
    */
    //=============================================================================
    //! 二次认证发送方式
    typedef TAPICHAR    TAPISendTypeType;
    //! 短信
    const TAPISendTypeType          TAPI_SENDTYPE_SMS = 'S';
    //! 邮件
    const TAPISendTypeType          TAPI_SENDTYPE_MAIL = 'M';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIDEVICETYPETYPE    手机设备类型
    *    @{
    */
    //=============================================================================
    //! 手机设备类型
    typedef TAPICHAR    TAPIDeviceTypeType;
    //! Android
    const TAPIDeviceTypeType        TAPI_DEVICETYPE_ANDROID = '0';
    //! IOS
    const TAPIDeviceTypeType        TAPI_DEVICETYPE_IOS = '1';

#pragma pack(pop)
}
#endif