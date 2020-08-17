//=============================================================================
/* 新易盛统一交易API接口
 * 该文件定义了EsTradeAPI 使用的数据结构
 * 版本信息:2018-05-21 郭晓刚 创建该文件
 */
//=============================================================================
#ifndef ES_TRADE_API_STRUCT_H
#define ES_TRADE_API_STRUCT_H

#include "EsTradeAPIDataType.h"

namespace EsTradeAPI
{

#pragma pack(push, 1)

//------------------------------------------------------------------------------------------
//! 登录用户信息
struct TapAPITradeUserInfo
{
    TAPISystemTypeType    SystemType;            ///< 后台系统类型
    TAPISTR_20            UserNo;                ///< 用户编号
    TAPISTR_40            LoginIP;            ///< 登录IP
    TAPIUINT32            LoginProt;            ///< 登录端口
    TAPILoginTypeType     LoginType;            ///< 登录类型
};

//! 登录认证信息
struct TapAPITradeLoginAuth
{
    TAPISTR_20            UserNo;                ///< 用户名
    TAPIUserTypeType    UserType;            ///< 用户类型
    TAPISTR_50            AuthCode;            ///< 授权码
    TAPISTR_30            AppID;                ///< 程序版本号
    TAPIYNFLAG            ISModifyPassword;            ///< 是否修改密码    
    TAPISTR_20            Password;            ///< 密码
    TAPISTR_20            NewPassword;        ///< 新密码
    TAPIYNFLAG            ISDDA;                ///< 是否需要动态认证
    TAPISTR_30            DDASerialNo;        ///< 动态认证码
    TAPINoticeIgnoreFlagType    NoticeIgnoreFlag;            ///< 忽略推送通知标记
    TAPISTR_300                 LoginInfo;                          ///< 直连用户请勿填写
};

//! 登录反馈信息
struct TapAPITradeLoginRspInfo
{
    TAPISTR_20            UserNo;                ///< 用户编号
    TAPIUserTypeType    UserType;            ///< 用户类型
    TAPISTR_20            UserName;            ///< 用户名
    TAPISTR_20            QuoteTempPassword;            ///< 行情临时密码
    TAPISTR_50            ReservedInfo;        ///< 预留信息
    TAPISTR_40            LastLoginIP;        ///< 上次登录IP
    TAPIUINT32            LastLoginProt;        ///< 上次登录端口
    TAPIDATETIME        LastLoginTime;        ///< 上次登录时间
    TAPIDATETIME        LastLogoutTime;        ///< 上次退出时间
    TAPIDATE            TradeDate;            ///< 当前交易日期
    TAPIDATETIME        LastSettleTime;        ///< 上次结算时间
    TAPIDATETIME        StartTime;            ///< 系统启动时间
    TAPIDATETIME        InitTime;            ///< 系统初始化时间
    TAPIAuthTypeType    AuthType;            ///< 用户授权类型
    TAPIDATETIME        AuthDate;            ///< 用户授权到期日
};

//! 登录采集信息
struct TapAPISubmitUserLoginInfo
{
    TAPISTR_20            UserNo;                ///< 登录用户名
    TAPISTR_500            GatherInfo;            ///< 用户终端信息
    TAPISTR_40            ClientLoginIP;        ///< 用户公网IP
    TAPIUINT32            ClientLoginPort;            ///< 用户公网Port
    TAPIDATETIME        ClientLoginDateTime;        ///< 用户登录时间
    TAPISTR_30            ClientAppID;        ///< 用户AppID
    TAPIUINT32            AuthKeyVersion;        ///< 用户终端信息加密密钥版本号
};

//! 上报用户登录采集信息应答
struct TapAPISubmitUserLoginInfoRsp
{
    TAPISTR_20            UserNo;                ///< 登录用户名
    TAPIUINT32            ErrorCode;            ///< 错误信息码
    TAPISTR_50            ErrorText;            ///< 错误信息
};

//! 交易所信息
struct TapAPIExchangeInfo
{
    TAPISTR_10            ExchangeNo;            ///< 交易所编码
    TAPISTR_20            ExchangeName;        ///< 交易所名称
};

//! 品种编码结构
struct TapAPICommodity
{
    TAPISTR_10            ExchangeNo;            ///< 交易所编码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编号
};

//! 交易品种信息
struct TapAPICommodityInfo
{
    TAPISTR_10            ExchangeNo;            ///< 交易所编码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编号
    TAPISTR_20            CommodityName;        ///< 品种名称
    TAPISTR_30            CommodityEngName;            ///< 品种英文名称
    TAPISTR_10            RelateExchangeNo;            ///< 关联品种交易所编码
    TAPICommodityType    RelateCommodityType;        ///< 关联品种品种类型
    TAPISTR_10            RelateCommodityNo;            ///< 关联品种品种编号
    TAPISTR_10            RelateExchangeNo2;            ///< 关联品种2交易所编码
    TAPICommodityType    RelateCommodityType2;        ///< 关联品种2品种类型
    TAPISTR_10            RelateCommodityNo2;            ///< 关联品种2品种编号
    TAPISTR_10            TradeCurrency;        ///< 交易币种
    TAPIREAL64            ContractSize;        ///< 每手乘数
    TAPIOpenCloseModeType        OpenCloseMode;        ///< 开平方式
    TAPIREAL64            StrikePriceTimes;            ///< 执行价格倍数
    TAPIREAL64            CommodityTickSize;            ///< 最小变动价位
    TAPIINT32            CommodityDenominator;        ///< 报价分母
    TAPICmbDirectType    CmbDirect;            ///< 组合方向
    TAPIINT32            OnlyCanCloseDays;            ///< 只可平仓提前天数
    TAPIDeliveryModeType        DeliveryMode;        ///< 交割行权方式
    TAPIINT32            DeliveryDays;        ///< 交割日偏移
    TAPITIME            AddOneTime;            ///< T+1分割时间
    TAPIINT32            CommodityTimeZone;            ///< 品种时区
    TAPIIsAddOneType    IsAddOne;            ///< 是否处于T+1时段
};

//! 合约编码结构
struct TapAPIContract
{
    TapAPICommodity        Commodity;            ///< 品种
    TAPISTR_10            ContractNo1;        ///< 合约代码1
    TAPISTR_10            StrikePrice1;        ///< 执行价1
    TAPICallOrPutFlagType        CallOrPutFlag1;        ///< 看涨看跌标示1
    TAPISTR_10            ContractNo2;        ///< 合约代码2
    TAPISTR_10            StrikePrice2;        ///< 执行价2
    TAPICallOrPutFlagType        CallOrPutFlag2;        ///< 看涨看跌标示2
};

//! 交易合约信息
struct TapAPITradeContractInfo
{
    TAPISTR_10            ExchangeNo;            ///< 交易所编码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编号
    TAPISTR_10            ContractNo1;        ///< 合约代码1
    TAPISTR_10            StrikePrice1;        ///< 执行价1
    TAPICallOrPutFlagType        CallOrPutFlag1;        ///< 看涨看跌标示1
    TAPISTR_10            ContractNo2;        ///< 合约代码2
    TAPISTR_10            StrikePrice2;        ///< 执行价2
    TAPICallOrPutFlagType        CallOrPutFlag2;        ///< 看涨看跌标示2
    TAPISTR_70            ContractName;        ///< 合约名称
    TAPIDATE            ContractExpDate;            ///< 合约到期日
    TAPIDATE            LastTradeDate;        ///< 最后交易日
    TAPIDATE            FirstNoticeDate;            ///< 首次通知日
    TAPISTR_10            FutureContractNo;            ///< 期货合约编号(期权标的)
};

//! 修改密码请求
struct TapAPIChangePasswordReq
{
    TAPISTR_20            OldPassword;        ///< 旧密码
    TAPISTR_20            NewPassword;        ///< 新密码
};

//! 用户权限信息
struct TapAPIUserRightInfo
{
    TAPISTR_20            UserNo;                ///< 用户编号
    TAPIRightIDType        RightID;            ///< 权限ID
};

//! 用户下单频率信息
struct TapAPIUserOrderFrequency
{
    TAPISTR_20            UserNo;                ///< 用户编号
    TAPIUINT32            UserOrderFrequency;            ///< 用户报单操作频率
};

//! 账号相关信息查询请求
struct TapAPIAccQryReq
{
    TAPISTR_20            AccountNo;            ///< 资金账号        
};

//! 资金账号信息
struct TapAPIAccountInfo
{
    TAPISTR_20            AccountNo;            ///< 资金账号
    TAPIAccountType        AccountType;        ///< 账号类型
    TAPIAccountState    AccountState;        ///< 账号状态
    TAPISTR_20            AccountShortName;            ///< 账号简称
    //TAPIYNFLAG        AccountIsDocHolder;            ///< 是否持证者
    TAPIYNFLAG            IsMarketMaker;        ///< 是否是做市商
    //TAPIAccountFamilyType        AccountFamilyType;            ///< 父子账号类型
};

//! 客户下单请求结构
struct TapAPINewOrder
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约1
    TAPISTR_10            StrikePrice;        ///< 执行价格1
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌1
    TAPISTR_10            ContractNo2;        ///< 合约2
    TAPISTR_10            StrikePrice2;        ///< 执行价格2
    TAPICallOrPutFlagType        CallOrPutFlag2;        ///< 看张看跌2
    TAPIOrderTypeType    OrderType;            ///< 委托类型
    TAPIOrderSourceType    OrderSource;        ///< 委托来源
    TAPITimeInForceType    TimeInForce;        ///< 委托有效类型
    TAPIDATETIME        ExpireTime;            ///< 有效日期(GTD情况下使用)
    TAPIYNFLAG            IsRiskOrder;        ///< 是否风险报单
    TAPISideType        OrderSide;            ///< 买入卖出
    TAPIPositionEffectType        PositionEffect;        ///< 开平标志1
    TAPIPositionEffectType        PositionEffect2;            ///< 开平标志2
    TAPISTR_50            InquiryNo;            ///< 询价号
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值1
    TAPIHedgeFlagType    HedgeFlag2;            ///< 投机保值2，做市商应价使用
    TAPIREAL64            OrderPrice;            ///< 委托价格1
    TAPIREAL64            OrderPrice2;        ///< 委托价格2，做市商应价使用
    TAPIUINT32            OrderQty;            ///< 委托数量1
    TAPIUINT32            OrderQty2;            ///< 委托数量2，做市商应价使用
    TAPIUINT32            OrderMinQty;        ///< 最小成交量
    TAPIUINT32            MinClipSize;        ///< 冰山单最小随机量
    TAPIUINT32            MaxClipSize;        ///< 冰山单最大随机量
    TAPIINT32            RefInt;                ///< 整型参考值
    TAPIREAL64            RefDouble;            ///< 浮点参考值(已弃用)
    TAPISTR_50            RefString;            ///< 字符串参考值
    TAPITacticsTypeType    TacticsType;        ///< 策略单类型
    TAPITriggerConditionType    TriggerCondition;            ///< 触发条件
    TAPITriggerPriceTypeType    TriggerPriceType;            ///< 触发价格类型
    TAPIREAL64            StopPrice;            ///< 触发价格
    TAPIYNFLAG            AddOneIsValid;        ///< 是否T+1有效
    TAPIMarketLevelType    MarketLevel;        ///< 市价撮合深度
    TAPIYNFLAG            FutureAutoCloseFlag;        ///< 行权后期货是否自对冲
    TAPISTR_10            UpperChannelNo;        ///< 上手通道号
    
    TapAPINewOrder()
    {
        memset(this, 0, sizeof(TapAPINewOrder));
        CallOrPutFlag = TAPI_CALLPUT_FLAG_NONE;
        CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
        OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;
        TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
        PositionEffect = TAPI_PositionEffect_NONE;
        PositionEffect2 = TAPI_PositionEffect_NONE;
        HedgeFlag = TAPI_HEDGEFLAG_NONE;
        HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
        TacticsType = TAPI_TACTICS_TYPE_NONE;
        TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
        TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;
        AddOneIsValid = APIYNFLAG_NO;
        FutureAutoCloseFlag = APIYNFLAG_NO;
    }
};

//! 委托完整信息
struct TapAPIOrderInfo
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约1
    TAPISTR_10            StrikePrice;        ///< 执行价格1
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌1
    TAPISTR_10            ContractNo2;        ///< 合约2
    TAPISTR_10            StrikePrice2;        ///< 执行价格2
    TAPICallOrPutFlagType        CallOrPutFlag2;        ///< 看张看跌2
    TAPIOrderTypeType    OrderType;            ///< 委托类型
    TAPIOrderSourceType    OrderSource;        ///< 委托来源
    TAPITimeInForceType    TimeInForce;        ///< 委托有效类型
    TAPIDATETIME        ExpireTime;            ///< 有效日期(GTD情况下使用)
    TAPIYNFLAG            IsRiskOrder;        ///< 是否风险报单
    TAPISideType        OrderSide;            ///< 买入卖出
    TAPIPositionEffectType        PositionEffect;        ///< 开平标志1
    TAPIPositionEffectType        PositionEffect2;            ///< 开平标志2，做市商应价使用
    TAPISTR_50            InquiryNo;            ///< 询价号
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值1
    TAPIHedgeFlagType    HedgeFlag2;            ///< 投机保值2，做市商应价使用
    TAPIREAL64            OrderPrice;            ///< 委托价格1
    TAPIREAL64            OrderPrice2;        ///< 委托价格2，做市商应价使用
    TAPIREAL64            StopPrice;            ///< 触发价格
    TAPIUINT32            OrderQty;            ///< 委托数量1
    TAPIUINT32            OrderQty2;            ///< 委托数量2，做市商应价使用
    TAPIUINT32            OrderMinQty;        ///< 最小成交量
    TAPIUINT32            MinClipSize;        ///< 冰山单最小随机量
    TAPIUINT32            MaxClipSize;        ///< 冰山单最大随机量
    TAPIINT32            RefInt;                ///< 整型参考值
    TAPIREAL64            RefDouble;            ///< 浮点参考值
    TAPISTR_50            RefString;            ///< 字符串参考值
    TAPITacticsTypeType    TacticsType;        ///< 策略单类型
    TAPITriggerConditionType    TriggerCondition;            ///< 触发条件
    TAPITriggerPriceTypeType    TriggerPriceType;            ///< 触发价格类型
    TAPIYNFLAG            AddOneIsValid;        ///< 是否T+1有效
    TAPIMarketLevelType    MarketLevel;        ///< 市价撮合深度
    TAPIYNFLAG            FutureAutoCloseFlag;        ///< 行权后期货是否自对冲
    
    TAPIUINT32            OrderCanceledQty;            ///< 撤单数量
    TAPISTR_50            LicenseNo;            ///< 软件授权号
    TAPISTR_20            ParentAccountNo;            ///< 上级资金账号

    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;            ///< 委托编码
    TAPISTR_50                  ClientOrderNo;        ///< 客户端本地委托编号
    TAPISTR_20            OrderLocalNo;        ///< 本地号
    TAPISTR_50            OrderSystemNo;        ///< 系统号
    TAPISTR_50            OrderExchangeSystemNo;        ///< 交易所系统号 
    //TAPISTR_20        OrderParentNo;        ///< 父单号
    //TAPISTR_50        OrderParentSystemNo;        ///< 父单系统号
    TAPISTR_10            TradeNo;            ///< 交易编码

    TAPISTR_10            UpperNo;            ///< 上手号
    TAPISTR_10            UpperChannelNo;        ///< 上手通道号
    TAPISTR_20            UpperSettleNo;        ///< 会员号和清算号
    TAPISTR_20            UpperUserNo;        ///< 上手登录号
    TAPISTR_20            OrderInsertUserNo;            ///< 下单人
    TAPIDATETIME        OrderInsertTime;            ///< 下单时间
    TAPISTR_20            OrderCommandUserNo;            ///< 录单操作人
    TAPISTR_20            OrderUpdateUserNo;            ///< 委托更新人
    TAPIDATETIME        OrderUpdateTime;            ///< 委托更新时间
    TAPIOrderStateType    OrderState;            ///< 委托状态
    TAPIREAL64            OrderMatchPrice;            ///< 成交价1
    TAPIREAL64            OrderMatchPrice2;            ///< 成交价2
    TAPIUINT32            OrderMatchQty;        ///< 成交量1
    TAPIUINT32            OrderMatchQty2;        ///< 成交量2

    TAPIUINT32            ErrorCode;            ///< 最后一次操作错误信息码
    TAPISTR_50            ErrorText;            ///< 错误信息

    TAPIYNFLAG            IsBackInput;        ///< 是否为录入委托单
    TAPIYNFLAG            IsDeleted;            ///< 委托成交删除标
    TAPIYNFLAG            IsAddOne;            ///< 是否为T+1单

    TAPIUINT32            OrderStreamID;        ///< 委托流水号
    //TAPIUINT32        UpperStreamID;        ///< 上手流号

    //TAPIREAL64        ContractSize;        ///< 每手乘数，计算参数
    //TAPIREAL64        ContractSize2;        ///< 每手乘数，计算参数
    //TAPISTR_10        CommodityCurrencyGroup;        ///< 品种币种组
    //TAPISTR_10        CommodityCurrency;            ///< 品种币种
    //TAPICalculateModeType        FeeMode;            ///< 手续费计算方式
    //TAPIREAL64        FeeParam;            ///< 手续费参数值 冻结手续费均按照开仓手续费计算
    //TAPISTR_10        FeeCurrencyGroup;            ///< 客户手续费币种组
    //TAPISTR_10        FeeCurrency;        ///< 客户手续费币种
    //TAPICalculateModeType        FeeMode2;            ///< 手续费计算方式
    //TAPIREAL64        FeeParam2;            ///< 手续费参数值 冻结手续费均按照开仓手续费计算
    //TAPISTR_10        FeeCurrencyGroup2;            ///< 客户手续费币种组
    //TAPISTR_10        FeeCurrency2;        ///< 客户手续费币种
    //TAPICalculateModeType        MarginMode;            ///< 保证金计算方式
    //TAPIREAL64        MarginParam;        ///< 保证金参数值
    //TAPICalculateModeType        MarginMode2;        ///< 保证金计算方式
    //TAPIREAL64        MarginParam2;        ///< 保证金参数值
    //TAPIREAL64        PreSettlePrice;        ///< 昨结算价  比例方式的市价单和组合订单使用
    //TAPIREAL64        PreSettlePrice2;            ///< 昨结算价  比例方式的市价单和组合订单使用
    //TAPIUINT32        OpenVol;            ///< 预开仓数量 委托数量中的开仓部分
    //TAPIUINT32        CoverVol;            ///< 预平仓数量 委托数量中的平仓部分
    //TAPIUINT32        OpenVol2;            ///< 预开仓数量 委托数量中的开仓部分
    //TAPIUINT32        CoverVol2;            ///< 预平仓数量 委托数量中的平仓部分
    TAPIREAL64            FeeValue;            ///< 冻结手续费
    TAPIREAL64            MarginValue;        ///< 冻结保证金 合并计算的此项为0
    TAPIYNFLAG            OrderDeleteByDisConnFlag;    ///< 心跳检测失败时，服务器自动撤单标识
    
    TapAPIOrderInfo()
    {
        memset(this, 0, sizeof(TapAPIOrderInfo));
        CallOrPutFlag = TAPI_CALLPUT_FLAG_NONE;
        CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
        OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;
        TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
        PositionEffect = TAPI_PositionEffect_NONE;
        PositionEffect2 = TAPI_PositionEffect_NONE;
        HedgeFlag = TAPI_HEDGEFLAG_NONE;
        HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
        TacticsType = TAPI_TACTICS_TYPE_NONE;
        AddOneIsValid = APIYNFLAG_NO;
        FutureAutoCloseFlag = APIYNFLAG_NO;
        IsBackInput = APIYNFLAG_NO;
        IsAddOne = APIYNFLAG_NO;
        IsDeleted = APIYNFLAG_NO;
        OrderDeleteByDisConnFlag = APIYNFLAG_NO;
    }
};

//! 报单操作应答结构
struct TapAPIOrderActionRsp
{
    TAPIORDERACT        ActionType;            ///< 操作类型
    TapAPIOrderInfo*    OrderInfo;            ///< 委托信息
};

//! 客户改单请求
//! 必填项有ServerFlag，OrderNo,以及委托价和委托量，止损价。其他字段暂时没有用。
struct TapAPIOrderModifyReq
{
    TapAPINewOrder        ReqData;            ///< 报单请求数据
    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;            ///< 委托编号
public:
    TapAPIOrderModifyReq()
    {
        memset(this, 0, sizeof(TapAPIOrderModifyReq));
    }
};

//! 客户撤单请求结构
//! 必填项是ServerFlag和OrderNo.
struct TapAPIOrderCancelReq
{
    TAPIINT32            RefInt;                ///< 整型参考值
    TAPISTR_50            RefString;            ///< 字符串参考值
    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;            ///< 委托编码
};

//! 挂起委托请求结构
typedef TapAPIOrderCancelReq TapAPIOrderDeactivateReq;

//! 激活委托请求结构
typedef TapAPIOrderCancelReq TapAPIOrderActivateReq;

//! 删除委托请求结构
typedef TapAPIOrderCancelReq TapAPIOrderDeleteReq;

//! 委托查询请求结构
struct TapAPIOrderQryReq
{
    TAPIOrderQryTypeType        OrderQryType;        ///< 委托查询类型
    TAPISTR_20            AccountNo;            ///< 客户资金帐号（填空查用户下属所有客户）
    TAPIUINT32            DataSeqID;            ///< 数据起始流号
};

//! 委托流程查询
struct TapAPIOrderProcessQryReq
{
    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;            ///< 委托编码
};

//! 成交查询请求结构
struct TapAPIFillQryReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号（填空查用户下属所有客户）
    TAPIUINT32            DataSeqID;            ///< 数据起始流号
};

//! 成交信息
struct TapAPIFillInfo
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号
    //TAPISTR_20        ParentAccountNo;            ///< 上级资金账号
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约1
    TAPISTR_10            StrikePrice;        ///< 执行价格
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌
    //TAPISTR_10        ExchangeNoRef;        ///< 交易所编号
    //TAPICommodityType    CommodityTypeRef;            ///< 品种类型
    //TAPISTR_10        CommodityNoRef;        ///< 品种编码类型
    //TAPISTR_10        ContractNoRef;        ///< 合约
    //TAPISTR_10        StrikePriceRef;        ///< 执行价格
    //TAPICallOrPutFlagType        CallOrPutFlagRef;            ///< 看张看跌
    //TAPISTR_10        OrderExchangeNo;            ///< 交易所编号
    //TAPICommodityType    OrderCommodityType;            ///< 品种类型
    //TAPISTR_10        OrderCommodityNo;            ///< 品种编码类型
    TAPIOrderTypeType    OrderType;            ///< 委托类型
    TAPIMatchSourceType    MatchSource;        ///< 委托来源
    TAPITimeInForceType    TimeInForce;        ///< 委托有效类型
    TAPIDATETIME        ExpireTime;            ///< 有效日期(GTD情况下使用)
    TAPIYNFLAG            IsRiskOrder;        ///< 是否风险报单
    TAPISideType        MatchSide;            ///< 买入卖出
    TAPIPositionEffectType        PositionEffect;        ///< 开平标志1
    //TAPIPositionEffectType    PositionEffectRef;            ///< 开平标志2
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值
    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;            ///< 委托编码
    TAPISTR_20            OrderLocalNo;        ///< 委托本地号
    TAPISTR_20            MatchNo;            ///< 本地成交号
    TAPISTR_70            ExchangeMatchNo;            ///< 交易所成交号
    TAPIDATETIME        MatchDateTime;        ///< 成交时间
    TAPIDATETIME        UpperMatchDateTime;            ///< 上手成交时间
    TAPISTR_10            UpperNo;            ///< 上手号
    TAPISTR_10            UpperChannelNo;        ///< 上手通道号
    TAPISTR_20            UpperSettleNo;        ///< 会员号和清算代码
    TAPISTR_20            UpperUserNo;        ///< 上手登录号
    TAPISTR_10            TradeNo;            ///< 交易编码
    TAPIREAL64            MatchPrice;            ///< 成交价
    TAPIUINT32            MatchQty;            ///< 成交量
    TAPIYNFLAG            IsBackInput;        ///< 是否为录入委托单
    TAPIYNFLAG            IsDeleted;            ///< 委托成交删除标
    TAPIYNFLAG            IsAddOne;            ///< 是否为T+1单
    TAPIUINT32            MatchStreamID;        ///< 委托流水号
    //TAPIUINT32        UpperStreamID;        ///< 上手流号
    TAPIOpenCloseModeType        OpenCloseMode;        ///< 开平方式
    TAPIREAL64            ContractSize;        ///< 每手乘数，计算参数
    TAPISTR_10            CommodityCurrencyGroup;        ///< 品种币种组
    TAPISTR_10            CommodityCurrency;            ///< 品种币种
    //TAPICalculateModeType        FeeMode;            ///< 手续费计算方式
    //TAPIREAL64        FeeParam;            ///< 手续费参数值 冻结手续费均按照开仓手续费计算
    TAPISTR_10            FeeCurrencyGroup;            ///< 客户手续费币种组
    TAPISTR_10            FeeCurrency;        ///< 客户手续费币种
    TAPIREAL64            PreSettlePrice;        ///< 昨结算价
    TAPIREAL64            FeeValue;            ///< 手续费
    TAPIYNFLAG            IsManualFee;        ///< 人工客户手续费标记
    //TAPIREAL64        Turnover;            ///< 成交金额
    TAPIREAL64            PremiumIncome;        ///< 权利金收取
    TAPIREAL64            PremiumPay;            ///< 权利金支付
    //TAPISTR_20        OppoMatchNo;        ///< 对手本地成交号（开仓和平仓对应编号）
    TAPIREAL64            CloseProfit;        ///< 平仓盈亏
    TAPIREAL64            UnExpProfit;        ///< 未到期平盈
    //TAPIREAL64        UpperMatchPrice;            ///< 上手成交价
    //TAPIREAL64        QuotePrice;            ///< 当前行情价
    TAPIREAL64            ClosePL;            ///< 逐笔平盈
};

//! 持仓查询请求结构
struct TapAPIPositionQryReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号（填空查用户下属所有客户）
    TAPIUINT32            DataSeqID;            ///< 数据起始流号
};

//! 持仓信息
struct TapAPIPositionInfo
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号
    //TAPISTR_20        ParentAccountNo;            ///< 上级资金账号
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约1
    TAPISTR_10            StrikePrice;        ///< 执行价格
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌
    //TAPISTR_10        ExchangeNoRef;        ///< 交易所编号
    //TAPICommodityType    CommodityTypeRef;            ///< 品种类型
    //TAPISTR_10        CommodityNoRef;        ///< 品种编码类型
    //TAPISTR_10        ContractNoRef;        ///< 合约
    //TAPISTR_10        StrikePriceRef;        ///< 执行价格
    //TAPICallOrPutFlagType        CallOrPutFlagRef;            ///< 看张看跌
    //TAPISTR_10        OrderExchangeNo;            ///< 交易所编号
    //TAPICommodityType    OrderCommodityType;            ///< 品种类型
    //TAPISTR_10        OrderCommodityNo;            ///< 品种编码类型
    //TAPIOrderTypeType    OrderType;            ///< 委托类型
    //TAPITimeInForceType        TimeInForce;        ///< 委托有效类型
    //TAPIDATETIME        ExpireTime;            ///< 有效日期(GTD情况下使用)
    TAPISideType        MatchSide;            ///< 买入卖出
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值
    TAPISTR_70            PositionNo;            ///< 本地持仓号，服务器编写
    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;            ///< 委托编码
    TAPISTR_20            MatchNo;            ///< 本地成交号
    TAPISTR_70            ExchangeMatchNo;            ///< 交易所成交号
    TAPIMatchSourceType    MatchSource;        ///< 委托来源
    //TAPIDATE            MatchDate;            ///< 成交日期
    //TAPIDATETIME        MatchTime;            ///< 成交时间
    //TAPIDATETIME        UpperMatchTime;        ///< 上手成交时间
    TAPISTR_10            UpperNo;            ///< 上手号
    TAPISTR_20            UpperSettleNo;        ///< 会员号和清算代码
    TAPISTR_20            UpperUserNo;        ///< 上手登录号
    TAPISTR_10            TradeNo;            ///< 交易编码
    TAPIREAL64            PositionPrice;        ///< 持仓价
    TAPIUINT32            PositionQty;        ///< 持仓量
    TAPIYNFLAG            IsBackInput;        ///< 是否为录入委托单
    TAPIYNFLAG            IsAddOne;            ///< 是否为T+1单
    TAPIUINT32            MatchStreamID;        ///< 成交流水号
    TAPIUINT32            PositionStreamId;            ///< 持仓流号
    //TAPIOpenCloseModeType        OpenCloseMode;                ///< 开平方式
    TAPIREAL64            ContractSize;        ///< 每手乘数，计算参数
    TAPISTR_10            CommodityCurrencyGroup;        ///< 品种币种组
    TAPISTR_10            CommodityCurrency;            ///< 品种币种
    TAPIREAL64            PreSettlePrice;        ///< 昨结算价
    //TAPIREAL64        SettlePrice;        ///< 当前计算价格
    TAPIREAL64            Turnover;            ///< 持仓金额
    TAPICalculateModeType        AccountMarginMode;            ///< 保证金计算方式
    TAPIREAL64            AccountMarginParam;            ///< 保证金参数值
    //TAPICalculateModeType        UpperMarginMode;            ///< 保证金计算方式
    //TAPIREAL64        UpperMarginParam;            ///< 保证金参数值
    TAPIREAL64            AccountInitialMargin;        ///< 客户初始保证金
    TAPIREAL64            AccountMaintenanceMargin;    ///< 客户维持保证金
    //TAPIREAL64        UpperInitialMargin;            ///< 上手初始保证金
    //TAPIREAL64        UpperMaintenanceMargin;        ///< 上手维持保证金
    TAPIREAL64            PositionProfit;        ///< 持仓盈亏
    TAPIREAL64            LMEPositionProfit;            ///< LME持仓盈亏
    TAPIREAL64            OptionMarketValue;            ///< 期权市值
    TAPISTR_20            MatchCmbNo;            ///< 组合持仓号
    TAPIYNFLAG            IsHistory;            ///< 是否历史持仓
    TAPIREAL64            FloatingPL;            ///< 逐笔浮盈
    TAPIREAL64            CalculatePrice;        ///< 计算价格
    
    TapAPIPositionInfo()
    {
        memset(this, 0, sizeof(TapAPIPositionInfo));
        IsBackInput = APIYNFLAG_NO;
        IsAddOne = APIYNFLAG_NO;
        IsHistory = APIYNFLAG_NO;
    }
};

//! 客户持仓盈亏
struct TapAPIPositionProfit
{
    TAPISTR_70            PositionNo;            ///< 本地持仓号，服务器编写
    TAPIUINT32            PositionStreamId;            ///< 持仓流号
    TAPIREAL64            PositionProfit;        ///< 持仓盈亏
    TAPIREAL64            LMEPositionProfit;            ///< LME持仓盈亏
    TAPIREAL64            OptionMarketValue;            ///< 期权市值
    TAPIREAL64            CalculatePrice;        ///< 计算价格
    TAPIREAL64            FloatingPL;            ///< 逐笔浮盈
};

//! 客户持仓盈亏通知
struct TapAPIPositionProfitNotice
{
    TAPIYNFLAG            IsLast;                ///< 是否最后一包
    TapAPIPositionProfit*        Data;                ///< 客户持仓盈亏信息
};

//! 平仓查询请求结构
struct TapAPICloseQryReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号（填空查用户下属所有客户）
    TAPIUINT32            DataSeqID;            ///< 数据起始流号
};

//! 平仓信息
struct TapAPICloseInfo
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号
    //TAPISTR_20        ParentAccountNo;            ///< 上级资金账号
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约
    TAPISTR_10            StrikePrice;        ///< 执行价格
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌
    //TAPISTR_10        OpenOrderExchangeNo;        ///< 交易所编号
    //TAPICommodityType    OpenOrderCommodityType;        ///< 品种类型
    //TAPISTR_10        OpenOrderCommodityNo;        ///< 品种编码类型
    //TAPISTR_10        CloseOrderExchangeNo;        ///< 交易所编号
    //TAPICommodityType    CloseOrderCommodityType;    ///< 品种类型
    //TAPISTR_10        CloseOrderCommodityNo;        ///< 品种编码类型
    TAPIMatchSourceType    OpenMatchSource;
    TAPIMatchSourceType    CloseMatchSource;
    TAPISideType        CloseSide;            ///< 平仓一边的买入卖出
    TAPIUINT32            CloseQty;            ///< 平仓成交量
    TAPIREAL64            OpenPrice;            ///< 开仓成交价
    TAPIREAL64            ClosePrice;            ///< 平仓成交价
    TAPICHAR            OpenServerFlag;        ///< 服务器标识
    TAPISTR_20            OpenOrderNo;        ///< 委托编码
    TAPISTR_20            OpenMatchNo;        ///< 本地成交号
    TAPISTR_70            OpenExchangeMatchNo;        ///< 交易所成交号
    TAPIDATETIME        OpenMatchDateTime;            ///< 成交时间
    TAPICHAR            CloseServerFlag;            ///< 服务器标识
    TAPISTR_20            CloseOrderNo;        ///< 委托编码
    TAPISTR_20            CloseMatchNo;        ///< 本地成交号
    TAPISTR_70            CloseExchangeMatchNo;        ///< 交易所成交号
    TAPIDATETIME        CloseMatchDateTime;            ///< 成交时间
    TAPIUINT32                  CloseStreamId;        ///< 平仓流号
    //TAPIOpenCloseModeType        OpenCloseMode;                ///< 开平方式
    TAPIREAL64            ContractSize;        ///< 每手乘数，计算参数
    //TAPISTR_10        CommodityCurrencyGroup;        ///< 品种币种组
    //TAPISTR_10        CommodityCurrency;            ///< 品种币种
    TAPIREAL64            PreSettlePrice;        ///< 昨结算价
    //TAPIREAL64        PremiumIncome;        ///< 权利金收取
    //TAPIREAL64        PremiumPay;            ///< 权利金支付
    TAPIREAL64            CloseProfit;        ///< 平仓盈亏
    TAPIREAL64            UnExpProfit;        ///< 未到期平盈
    TAPIREAL64            ClosePL;            ///< 逐笔平盈
};

//! 资金查询请求
struct TapAPIFundReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金帐号
    TAPIUINT32            DataSeqID;            ///< 数据查询起始流号（1表示第一个数据，本次查询包含这个编号的数据）
};

//! 资金账号资金信息
struct TapAPIFundData
{
    TAPISTR_20            AccountNo;            ///< 客户资金账号
    //TAPISTR_20        ParentAccountNo;            ///< 上级资金账号
    TAPISTR_10            CurrencyGroupNo;            ///< 币种组号
    TAPISTR_10            CurrencyNo;            ///< 币种号(为空表示币种组基币资金)
    TAPIREAL64            TradeRate;            ///< 交易汇率
    TAPIFutureAlgType    FutureAlg;            ///< 期货算法
    TAPIOptionAlgType    OptionAlg;            ///< 期权算法
    TAPIREAL64            PreBalance;            ///< 上日结存
    TAPIREAL64            PreUnExpProfit;        ///< 上日未到期平盈
    TAPIREAL64            PreLMEPositionProfit;        ///< 上日LME持仓平盈
    TAPIREAL64            PreEquity;            ///< 上日权益
    TAPIREAL64            PreAvailable1;        ///< 上日可用
    TAPIREAL64            PreMarketEquity;            ///< 上日市值权益
    TAPIREAL64            CashInValue;        ///< 入金
    TAPIREAL64            CashOutValue;        ///< 出金
    TAPIREAL64            CashAdjustValue;            ///< 资金调整
    TAPIREAL64            CashPledged;        ///< 质押资金
    TAPIREAL64            FrozenFee;            ///< 冻结手续费
    TAPIREAL64            FrozenDeposit;        ///< 冻结保证金
    TAPIREAL64            AccountFee;            ///< 客户手续费包含交割手续费
    TAPIREAL64            ExchangeFee;        ///< 汇兑手续费
    TAPIREAL64            AccountDeliveryFee;            ///< 客户交割手续费
    TAPIREAL64            PremiumIncome;        ///< 权利金收取
    TAPIREAL64            PremiumPay;            ///< 权利金支付
    TAPIREAL64            CloseProfit;        ///< 平仓盈亏
    TAPIREAL64            DeliveryProfit;        ///< 交割盈亏
    TAPIREAL64            UnExpProfit;        ///< 未到期平盈
    TAPIREAL64            ExpProfit;            ///< 到期平仓盈亏
    TAPIREAL64            PositionProfit;        ///< 不含LME持仓盈亏 
    TAPIREAL64            LmePositionProfit;            ///< LME持仓盈亏
    TAPIREAL64            OptionMarketValue;            ///< 期权市值
    TAPIREAL64            AccountInitialMargin;        ///< 客户初始保证金
    TAPIREAL64            AccountMaintenanceMargin;    ///< 客户维持保证金
    TAPIREAL64            UpperInitialMargin;            ///< 上手初始保证金
    TAPIREAL64            UpperMaintenanceMargin;        ///< 上手维持保证金
    TAPIREAL64            Discount;            ///< LME贴现
    TAPIREAL64            Balance;            ///< 当日结存
    TAPIREAL64            Equity;                ///< 当日权益
    TAPIREAL64            Available;            ///< 当日可用
    TAPIREAL64            CanDraw;            ///< 可提取
    TAPIREAL64            MarketEquity;        ///< 账户市值
    TAPIREAL64            AuthMoney;            ///< 授信资金
    TAPIREAL64            OriginalCashInOut;            ///< 币种原始出入金
    TAPIREAL64            FloatingPL;            ///< 逐笔浮盈
    TAPIREAL64            FrozenRiskFundValue;        ///< 风险冻结资金
    TAPIREAL64            ClosePL;            ///< 逐笔平盈
    TAPIREAL64            NoCurrencyPledgeValue;        ///< 非货币质押
    TAPIREAL64            PrePledgeValue;        ///< 期初质押
    TAPIREAL64            PledgeIn;            ///< 质入
    TAPIREAL64            PledgeOut;            ///< 质出
    TAPIREAL64            PledgeValue;        ///< 质押余额
    TAPIREAL64            BorrowValue;        ///< 借用金额
    TAPIREAL64            SpecialAccountFrozenMargin;    ///< 特殊产品冻结保证金
    TAPIREAL64            SpecialAccountMargin;        ///< 特殊产品保证金   
    TAPIREAL64            SpecialAccountFrozenFee;    ///< 特殊产品冻结手续费
    TAPIREAL64            SpecialAccountFee;            ///< 特殊产品手续费
    TAPIREAL64            SpecialFloatProfit;            ///< 特殊产品浮盈
    TAPIREAL64            SpecialCloseProfit;            ///< 特殊产品平盈
    TAPIREAL64            SpecialFloatPL;        ///< 特殊产品逐笔浮盈
    TAPIREAL64            SpecialClosePL;        ///< 特殊产品逐笔平盈
    TAPIREAL64            RiskRate;            ///< 风险率
};

//! 做市商询价通知结构
struct TapAPIReqQuoteNotice
{
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约
    TAPISTR_10            StrikePrice;        ///< 执行价格
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌
    TAPISTR_50            InquiryNo;            ///< 询价号
    TAPIDATETIME        UpdateTime;            ///< 更新时间                   
};

//! 深度行情信息(启明星专用)
struct TapAPIDeepQuoteInfo
{
    TAPISideType        Side;                ///< 买卖方向
    TAPIREAL64            Price;                ///< 挂单价格
    TAPIUINT32            Qty;                ///< 挂单数量
};

//! 深度行情查询应答(启明星专用)
struct TapAPIDeepQuoteQryRsp
{
    TapAPIContract        Contract;            ///< 合约
    TapAPIDeepQuoteInfo    DeepQuote;            ///< 深度行情
};

//! 交易所时间状态信息查询请求结构(启明星专用)
struct TapAPIExchangeStateInfoQryReq
{
};

//! 交易所时间状态信息(启明星专用)
struct TapAPIExchangeStateInfo
{
    TAPISTR_10            UpperChannelNo;        ///< 上手通道编号
    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编号
    TAPIDATETIME        ExchangeTime;        ///< 交易所时间
    TAPITradingStateType        TradingState;        ///< 交易所状态
};

//! 交易所时间状态信息通知结构(启明星专用)
struct TapAPIExchangeStateInfoNotice
{
    TAPIYNFLAG            IsLast;                ///< 是否最后一包数据
    TapAPIExchangeStateInfo        ExchangeStateInfo;            ///< 交易所时间状态信息
};

//! 上手通道信息查询请求结构(启明星专用)
struct TapAPIUpperChannelQryReq
{
};

//! 上手通道信息结构(启明星专用)
struct TapAPIUpperChannelInfo
{
    TAPISTR_10            UpperChannelNo;        ///< 上手通道编号
    TAPISTR_20            UpperChannelName;            ///< 上手通道名称
    TAPISTR_10            UpperNo;            ///< 上手通道号
    TAPISTR_20            UpperUserNo;        ///< 内盘席位号
};

//! 客户最终费率查询请求结构
struct TapAPIAccountRentQryReq
{
    TAPISTR_20            AccountNo;            ///< 资金账户
    TAPISTR_10            ExchangeNo;            ///< 交易所编码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编号
    TAPISTR_10            ContractNo;            ///< 合约代码 
};

//! 客户最终费率信息结构
struct    TapAPIAccountRentInfo
{
    TAPISTR_20            AccountNo;            ///< 资金账户
    TAPISTR_10            ExchangeNo;            ///< 交易所编码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编号
    TAPISTR_10            ContractNo;            ///< 合约代码 
    TAPIMatchSourceType    MatchSource;        ///< 成交来源  
    TAPISTR_10            CurrencyNo;            ///< 币种编号
    
    TAPICalculateModeType        FeeMode;            ///< 手续费计算方式 
    TAPIREAL64            OpenTurnover;        ///< 开仓手续费按金额
    TAPIREAL64            ClosedTurnover;        ///< 平仓手续费按金额
    TAPIREAL64            CloseNewTurnover;            ///< 平今手续费按金额
    TAPIREAL64            OpenVolume;            ///< 开仓手续费按手数
    TAPIREAL64            ClosedVolume;        ///< 平仓手续费按手数    
    TAPIREAL64            CloseNewVolume;        ///< 平今手续费按手数
    
    TAPICalculateModeType        MarginMode;            ///< 保证金计算方式   
    TAPIREAL64            BuyTInitMargin;        ///< 买投机初始保证金
    TAPIREAL64            SellTInitMargin;            ///< 卖投机初始保证金
    TAPIREAL64            BuyBInitMargin;        ///< 买保值初始保证金
    TAPIREAL64            SellBInitMargin;            ///< 卖保值初始保证金
    TAPIREAL64            BuyLInitMargin;        ///< 买套利初始保证金
    TAPIREAL64            SellLInitMargin;            ///< 卖套利初始保证金
    TAPIREAL64            BuyMInitMargin;        ///< 买做市商初始保证金
    TAPIREAL64            SellMInitMargin;            ///< 卖做市商初始保证金
    TAPIREAL64            BuyTMaintMargin;            ///< 买投机维持保证金
    TAPIREAL64            SellTMaintMargin;            ///< 卖投机维持保证金
    TAPIREAL64            BuyBMaintMargin;            ///< 买保值维持保证金
    TAPIREAL64            SellBMaintMargin;            ///< 卖保值维持保证金
    TAPIREAL64            BuyLMaintMargin;            ///< 买套利维持保证金
    TAPIREAL64            SellLMaintMargin;            ///< 卖套利维持保证金
    TAPIREAL64            BuyMMaintMargin;            ///< 买做市商维持保证金
    TAPIREAL64            SellMMaintMargin;            ///< 卖做市商维持保证金
};

//! 交易币种信息(北斗星专用)
struct TapAPICurrencyInfo
{
    TAPISTR_10            CurrencyNo;        ///< 币种编号
    TAPISTR_10            CurrencyGroupNo;        ///< 币种组编号
    TAPIREAL64            TradeRate;        ///< 交易汇率
    TAPIREAL64            TradeRate2;        ///< 交易汇率2

    TAPIFutureAlgType    FutureAlg;        ///< 逐笔'1',盯市 '2'
    TAPIOptionAlgType    OptionAlg;        ///< 期权算法,期货方式'1',期权方式'2'
};

//! 交易消息查询结构(启明星、北斗星专用)
struct TapAPITradeMessageQryReq
{
    TAPIUINT32            SerialID;        ///< 流号
    TAPIMsgQryTypeType          TradeMsgQryType;                ///< 查询类型(北斗星专用，启明星默认为全部)
    TAPISTR_20            AccountNo;        ///< 客户资金账号
    TAPIDATETIME                BeginSendDateTime;              ///< 开始时间
    TAPIDATETIME                EndSendDateTime;                ///< 结束时间
};

//! 交易消息结构(启明星、北斗星专用)
struct TapAPITradeMessage
{
    TAPIUINT32            SerialID;        ///< 流号
    TAPISTR_20            AccountNo;        ///< 客户资金账号

    TAPIDATETIME        TMsgValidDateTime;        ///< 消息有效时间
    TAPISTR_50            TMsgTitle;        ///< 消息标题
    TAPISTR_500            TMsgContent;            ///< 消息内容
    TAPIMsgTypeType        TMsgType;        ///< 消息类型
    TAPIMsgLevelType    TMsgLevel;        ///< 消息级别

    TAPIYNFLAG            IsSendBySMS;            ///< 是否发送短信
    TAPIYNFLAG            IsSendByEMail;            ///< 是否发送邮件
    TAPISTR_20            Sender;            ///<发送者
    TAPIDATETIME        SendDateTime;            ///< 发送时间
};

//! 客户资金调整查询请求结构(北斗星专用)
struct TapAPIAccountCashAdjustQryReq
{
    TAPIUINT32            SerialID;
    TAPISTR_20            AccountNo;
    TAPISTR_20            AccountAttributeNo;        ///< 客户属性
    TAPIDATE            BeginDate;        ///< 必填
    TAPIDATE            EndDate;        ///< 必填
};

//! 客户资金调整查询应答结构(北斗星专用)
struct TapAPIAccountCashAdjustQryRsp
{
    TAPIDATE            Date;            ///< 日期
    TAPISTR_20            AccountNo;        ///< 客户资金账号

    TAPICashAdjustTypeType        CashAdjustType;            ///< 资金调整类型
    TAPISTR_10            CurrencyGroupNo;        ///< 币种组号
    TAPISTR_10            CurrencyNo;        ///< 币种号
    TAPIREAL64            CashAdjustValue;        ///< 资金调整金额
    TAPISTR_100            CashAdjustRemark;        ///< 资金调整备注

    TAPIDATETIME        OperateTime;            ///< 操作时间
    TAPISTR_20            OperatorNo;        ///< 操作员

    TAPISTR_10            AccountBank;            ///< 客户银行
    TAPISTR_20            BankAccount;            ///< 客户银行账号
    TAPIBankAccountLWFlagType    AccountLWFlag;            ///< 客户本外币标识
    TAPISTR_10            CompanyBank;            ///< 公司银行
    TAPISTR_20            InternalBankAccount;    ///< 公司银行账户
    TAPIBankAccountLWFlagType    CompanyLWFlag;            ///< 公司本外币标识
};

//! 客户账单查询请求结构(北斗星专用)
struct TapAPIBillQryReq
{
    TAPISTR_20            UserNo;
    TAPIBillTypeType    BillType;
    TAPIDATE            BillDate;
    TAPIBillFileTypeType        BillFileType;
};

//! 客户账单查询应答结构(北斗星专用)
struct TapAPIBillQryRsp
{
    TapAPIBillQryReq    Reqdata;
    TAPIINT32            BillLen;
    TAPICHAR            BillText[1];    ///< 变长账单内容，长度由BillLen指定
};
    
//! 历史委托查询请求结构(北斗星专用)
struct TapAPIHisOrderQryReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金账号
    TAPISTR_20            AccountAttributeNo;            ///< 客户属性号
    TAPIDATE            BeginDate;            ///< 开始时间 (必填)
    TAPIDATE            EndDate;            ///< 结束时间 (必填)
};

//! 历史委托查询应答结构(北斗星专用)
struct TapAPIHisOrderQryRsp
{
    TAPIDATE            Date;                ///< 日期
    TAPISTR_20            AccountNo;            ///< 客户资金账号

    TAPISTR_10            ExchangeNo;            ///< 交易所编号
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码类型
    TAPISTR_10            ContractNo;            ///< 合约
    TAPISTR_10            StrikePrice;        ///< 执行价格
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看张看跌
    TAPISTR_10            ContractNo2;        ///< 合约2
    TAPISTR_10            StrikePrice2;        ///< 执行价格2
    TAPICallOrPutFlagType        CallOrPutFlag2;        ///< 看张看跌2

    TAPIOrderTypeType    OrderType;            ///< 委托类型
    TAPIOrderSourceType    OrderSource;        ///< 委托来源
    TAPITimeInForceType    TimeInForce;        ///< 委托有效类型
    TAPIDATETIME        ExpireTime;            ///< 有效日期(GTD情况下使用)
    TAPIYNFLAG            IsRiskOrder;        ///< 是否风险报单
    TAPISideType        OrderSide;            ///< 买入卖出
    TAPIPositionEffectType        PositionEffect;        ///< 开平标志
    TAPIPositionEffectType        PositionEffect2;            ///< 开平标志2
    TAPISTR_50            InquiryNo;            ///< 询价号
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值
    TAPIREAL64            OrderPrice;            ///< 委托价格
    TAPIREAL64            OrderPrice2;        ///< 委托价格2，做市商应价使用
    TAPIREAL64            StopPrice;            ///< 触发价格
    TAPIUINT32            OrderQty;            ///< 委托数量
    TAPIUINT32            OrderMinQty;        ///< 最小成交量
    TAPIUINT32            OrderCanceledQty;            ///< 撤单数量

    TAPIINT32            RefInt;                ///< 整型参考值
    TAPIREAL64            RefDouble;            ///<浮点参考型。
    TAPISTR_50            RefString;            ///< 字符串参考值

    TAPICHAR            ServerFlag;            ///< 服务器标识
    TAPISTR_20            OrderNo;                                            ///< 委托编码
    TAPIUINT32            OrderStreamID;        ///< 委托流水号

    TAPISTR_10            UpperNo;            ///< 上手号
    TAPISTR_10            UpperChannelNo;        ///< 上手通道编号
    TAPISTR_20            OrderLocalNo;        ///< 本地号
    TAPIUINT32            UpperStreamID;        ///< 上手流号

    TAPISTR_50            OrderSystemNo;        ///< 系统号
    TAPISTR_50            OrderExchangeSystemNo;        ///< 交易所系统号
    TAPISTR_50            OrderParentSystemNo;        ///< 父单系统号 

    TAPISTR_20            OrderInsertUserNo;            ///< 下单人
    TAPIDATETIME        OrderInsertTime;            ///< 下单时间
    TAPISTR_20            OrderCommandUserNo;            ///< 指令下达人
    TAPISTR_20            OrderUpdateUserNo;            ///< 委托更新人
    TAPIDATETIME        OrderUpdateTime;            ///< 委托更新时间

    TAPIOrderStateType    OrderState;            ///< 委托状态

    TAPIREAL64            OrderMatchPrice;            ///< 成交价
    TAPIREAL64            OrderMatchPrice2;            ///< 成交价2
    TAPIUINT32            OrderMatchQty;        ///< 成交量
    TAPIUINT32            OrderMatchQty2;        ///< 成交量2

    TAPIUINT32            ErrorCode;            ///< 最后一次操作错误信息码
    TAPISTR_50            ErrorText;            ///< 错误信息

    TAPIYNFLAG            IsBackInput;        ///< 是否为录入委托单
    TAPIYNFLAG            IsDeleted;            ///< 委托成交删除标记
    TAPIYNFLAG            IsAddOne;            ///< 是否为T+1单
    TAPIYNFLAG            AddOneIsValid;        ///< 是否T+1有效

    TAPIUINT32            MinClipSize;        ///< 冰山单最小随机量
    TAPIUINT32            MaxClipSize;        ///< 冰山单最大随机量
    TAPISTR_50            LicenseNo;            ///< 软件授权号

    TAPITacticsTypeType    TacticsType;        ///< 策略单类型    
    TAPITriggerConditionType    TriggerCondition;            ///< 触发条件
    TAPITriggerPriceTypeType    TriggerPriceType;            ///< 触发价格类型
};

//! 历史成交查询请求结构(北斗星专用)
struct TapAPIHisFillQryReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金账号
    TAPISTR_20            AccountAttributeNo;            ///< 客户属性号
    TAPIDATE            BeginDate;            ///< 开始日期，必填
    TAPIDATE            EndDate;            ///< 结束日期，必填
    TAPICHAR            CountType;            ///< 统计类型
};

//! 历史成交查询应答结构(北斗星专用)
//! key1=SerialID
//! key2=ExchangeNo+MatchCmbNo+MatchNo+MatchSide
struct TapAPIHisFillQryRsp
{
    TAPIDATE            SettleDate;            ///< 结算日期
    TAPIDATE            TradeDate;            ///<交易日期
    TAPISTR_20            AccountNo;            ///< 客户资金账号

    TAPISTR_10            ExchangeNo;            ///< 市场或者交易所代码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种号
    TAPISTR_10            ContractNo;            ///< 合约号
    TAPISTR_10            StrikePrice;        ///< 执行价
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看涨看跌标志

    TAPIMatchSourceType    MatchSource;        ///< 成交来源    
    TAPISideType        MatchSide;            ///< 买卖方向
    TAPIPositionEffectType        PositionEffect;        ///< 开平标志
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值
    TAPIREAL64            MatchPrice;            ///< 成交价
    TAPIUINT32            MatchQty;            ///< 成交量

    TAPISTR_20            OrderNo;            ///< 委托号
    TAPISTR_20            MatchNo;            ///< 成交序号
    TAPIUINT32            MatchStreamID;        ///< 成交流水号

    TAPISTR_10            UpperNo;            ///< 上手号
    TAPISTR_20            MatchCmbNo;            ///< 组合号
    TAPISTR_70            ExchangeMatchNo;            ///< 成交编号(交易所成交号)
    TAPIUINT32            MatchUpperStreamID;            ///< 上手流水号

    TAPISTR_10            CommodityCurrencyGroup;
    TAPISTR_10            CommodityCurrency;            ///< 品种币种        

    TAPIREAL64            Turnover;            ///< 成交金额
    TAPIREAL64            PremiumIncome;        ///< 权利金收入
    TAPIREAL64            PremiumPay;            ///< 权利金支出

    TAPIREAL64            AccountFee;            ///< 客户手续费
    TAPISTR_10            AccountFeeCurrencyGroup;
    TAPISTR_10            AccountFeeCurrency;            ///< 客户手续费币种
    TAPIYNFLAG            IsManualFee;        ///< 人工客户手续费标记
    TAPIREAL64            AccountOtherFee;            ///< 客户其他费用

    TAPIREAL64            UpperFee;            ///< 上手手续费
    TAPISTR_10            UpperFeeCurrencyGroup;
    TAPISTR_10            UpperFeeCurrency;            ///< 上手手续费币种
    TAPIYNFLAG            IsUpperManualFee;            ///< 人工上手手续费标记
    TAPIREAL64            UpperOtherFee;        ///< 上手其他费用

    TAPIDATETIME        MatchDateTime;        ///< 成交时间
    TAPIDATETIME        UpperMatchDateTime;            ///< 上手成交时间

    TAPIREAL64            CloseProfit;        ///< 平仓盈亏
    TAPIREAL64            ClosePrice;            ///< 指定平仓价格；    

    TAPIUINT32            CloseQty;            ///< 平仓量

    TAPISTR_10            SettleGroupNo;        ///<结算分组
    TAPISTR_20            OperatorNo;            ///< 操作员
    TAPIDATETIME        OperateTime;        ///< 操作时间
};

//! 历史委托流程查询请求结构(北斗星专用)
struct TapAPIHisOrderProcessQryReq
{
    TAPIDATE            Date;
    TAPISTR_20            OrderNo;
};

//! 历史委托流程查询应答数据结构(北斗星专用)
typedef TapAPIHisOrderQryRsp        TapAPIHisOrderProcessQryRsp;

//! 历史持仓查询请求结构(北斗星专用)
struct TapAPIHisPositionQryReq
{
    TAPISTR_20            AccountNo;        ///< 客户资金账号
    TAPISTR_20            AccountAttributeNo;        ///< 客户属性号
    TAPIDATE            Date;            ///< 日期
    TAPICHAR            CountType;        ///< 统计类型
};

//! 历史持仓查询数据应答结构(北斗星专用)
//! key1=SerialID
//! key2=结算日期+交易所+组号编号+持仓编号+买卖方向
struct TapAPIHisPositionQryRsp
{
    TAPIDATE            SettleDate;            ///< 结算日期
    TAPIDATE            OpenDate;            ///< 开仓日期

    TAPISTR_20            AccountNo;            ///< 客户资金账号

    TAPISTR_10            ExchangeNo;            ///< 市场或者交易所代码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码
    TAPISTR_10            ContractNo;            ///< 合约号
    TAPISTR_10            StrikePrice;        ///< 执行价
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看涨看跌标志

    TAPISideType        MatchSide;            ///< 买卖方向
    TAPIHedgeFlagType    HedgeFlag;            ///< 投机保值
    TAPIREAL64            PositionPrice;        ///< 持仓价格
    TAPIUINT32            PositionQty;        ///< 持仓量

    TAPISTR_20            OrderNo;            ///< 
    TAPISTR_70            PositionNo;            ///< 持仓编号

    TAPISTR_10            UpperNo;            ///< 上手号    

    TAPISTR_10            CurrencyGroup;        ///< 品种币种组
    TAPISTR_10            Currency;            ///< 品种币种

    TAPIREAL64            PreSettlePrice;        ///< 上日结算价格
    TAPIREAL64            SettlePrice;        ///< 结算价格
    TAPIREAL64            PositionDProfit;            ///< 持仓盈亏(盯市)
    TAPIREAL64            LMEPositionProfit;            ///< LME持仓盈亏
    TAPIREAL64            OptionMarketValue;            ///< 期权市值

    TAPIREAL64            AccountInitialMargin;        ///< 客户初始保证金
    TAPIREAL64            AccountMaintenanceMargin;    ///< 客户维持保证金
    TAPIREAL64            UpperInitialMargin;            ///< 上手初始保证金
    TAPIREAL64            UpperMaintenanceMargin;        ///< 上手维持保证金

    TAPISTR_10            SettleGroupNo;        ///< 结算分组
};

//! 交割查询请求结构(北斗星专用)
struct TapAPIHisDeliveryQryReq
{
    TAPISTR_20            AccountNo;            ///< 客户资金账号
    TAPISTR_20            AccountAttributeNo;            ///< 客户属性号
    TAPIDATE            BeginDate;            ///< 开始日期（必填）
    TAPIDATE            EndDate;            ///< 结束日期（必填）
    TAPICHAR            CountType;            ///< 统计类型
};

//! 交割查询应答数据结构(北斗星专用)
//! key1=SerialID
struct TapAPIHisDeliveryQryRsp
{
    TAPIDATE            DeliveryDate;        ///< 交割日期
    TAPIDATE            OpenDate;            ///< 开仓日期
    TAPISTR_20            AccountNo;            ///< 客户资金账号

    TAPISTR_10            ExchangeNo;            ///< 市场号或交易所代码
    TAPICommodityType    CommodityType;        ///< 品种类型
    TAPISTR_10            CommodityNo;        ///< 品种编码
    TAPISTR_10            ContractNo;            ///< 合约编码
    TAPISTR_10            StrikePrice;        ///< 执行价
    TAPICallOrPutFlagType        CallOrPutFlag;        ///< 看涨看跌标志

    TAPIMatchSourceType    MatchSource;        ///< 成交来源
    TAPISideType        OpenSide;            ///< 开仓方向
    TAPIREAL64            OpenPrice;            ///< 开仓价格
    TAPIREAL64            DeliveryPrice;        ///< 交割价格
    TAPIUINT32            DeliveryQty;        ///< 交割量
    TAPIUINT32            FrozenQty;            ///< 冻结量

    TAPISTR_20            OpenNo;                ///< 开仓成交号
    TAPISTR_10            UpperNo;            ///< 上手编号

    TAPISTR_10            CommodityCurrencyGroupy;    ///< 品种币种
    TAPISTR_10            CommodityCurrency;            ///< 品种币种
    TAPIREAL64            PreSettlePrice;        ///< 上日结算价
    TAPIREAL64            DeliveryProfit;        ///< 交割盈亏

    TAPIREAL64            AccountFrozenInitialMargin;    ///< 客户初始冻结保证金
    TAPIREAL64            AccountFrozenMaintenanceMargin;        ///< 客户维持冻结保证金
    TAPIREAL64            UpperFrozenInitialMargin;    ///< 上手初始冻结保证金
    TAPIREAL64            UpperFrozenMaintenanceMargin;        ///< 上手维持冻结保证金

    TAPISTR_10            AccountFeeCurrencyGroup;
    TAPISTR_10            AccountFeeCurrency;            ///< 客户手续费币种
    TAPIREAL64            AccountDeliveryFee;            ///< 客户交割手续费 
    TAPISTR_10            UpperFeeCurrencyGroup;
    TAPISTR_10            UpperFeeCurrency;            ///< 上手手续费币种
    TAPIREAL64            UpperDeliveryFee;            ///< 上手交割手续费

    TAPIDeliveryModeType        DeliveryMode;        ///< 交割行权方式
    TAPISTR_20            OperatorNo;            ///< 操作员
    TAPIDATETIME        OperateTime;        ///< 操作时间
    TAPISTR_20            SettleGourpNo;        ///< 结算分组
};

//! 客户账户手续费计算参数查询请求结构（北斗星专用）
struct TapAPIAccountFeeRentQryReq
{
    TAPISTR_20        AccountNo;
};
//! 客户账户手续费计算参数查询应答结构（北斗星专用）
struct TapAPIAccountFeeRentQryRsp
{
    TAPISTR_20        AccountNo;
    TAPISTR_10        ExchangeNo;
    TAPICommodityType        CommodityType;
    TAPISTR_10        CommodityNo;
    TAPIMatchSourceType        MatchSource;
    TAPICalculateModeType    CalculateMode;
    TAPISTR_10        CurrencyGroupNo;
    TAPISTR_10        CurrencyNo;    
    TAPIREAL64        OpenCloseFee;
    TAPIREAL64        CloseTodayFee;
};

//! 客户账户保证金计算参数查询结构（北斗星专用）
struct TapAPIAccountMarginRentQryReq
{
    TAPISTR_20        AccountNo;
    TAPISTR_10        ExchangeNo;
    TAPICommodityType        CommodityType;
    TAPISTR_10        CommodityNo;
    //TAPISTR_10            ContractNo;//暂时先不对外开放。
};

//! 客户账户保证金计算参数查询应答（北斗星专用）
struct TapAPIAccountMarginRentQryRsp
{
    TAPISTR_20        AccountNo;
    TAPISTR_10        ExchangeNo;
    TAPICommodityType        CommodityType;
    TAPISTR_10        CommodityNo;
    TAPISTR_10        ContractNo;
    TAPISTR_10        StrikePrice;
    TAPICallOrPutFlagType    CallOrPutFlag;
    TAPICalculateModeType    CalculateMode;
    TAPISTR_10        CurrencyGroupNo;
    TAPISTR_10        CurrencyNo;
    TAPIREAL64        InitialMargin;
    TAPIREAL64        MaintenanceMargin;
    TAPIREAL64        SellInitialMargin;
    TAPIREAL64        SellMaintenanceMargin;
    TAPIREAL64        LockMargin;
};

//! 二次认证信息请求应答结构
struct TapAPISecondInfo
{
    TAPISendTypeType               SendType;           ///< 发送类型
    TAPISTR_40                     SendAccount;        ///< 发送账号(手机号或者邮箱)
};

//! 请求二次认证授权码应答
struct TapAPIVertificateCode
{
    TAPISecondSerialIDType SecondSerialID;        ///< 二次认证授权码序号
    TAPIINT32              Effective;            ///< 二次认证授权码有效期（分）。
};

//! 登录用户手机设备增加请求结构
struct TapAPIMobileDeviceAddReq
{
    TAPISTR_20            UserNo;                ///< 用户编号
    TAPISTR_30                  AppKey;
    TAPISTR_30                  AppID;
    TAPISTR_30                  MasterSecret;
    TAPISTR_50                  Cid;
    TAPISTR_10                  CompanyNo;
    TAPISTR_20                  CompanyAddressNo;
    TAPIDeviceTypeType          DeviceType;
};

//! 登录用户手机设备增加应答结构
typedef TapAPIMobileDeviceAddReq  TapAPIMobileDeviceAddRsp;

//! 管理日志查询请求结构
struct TapAPIManageInfoQryReq
{
    TAPIDATE                BeginDate;        ///< 开始日期，必填
    TAPIDATE        EndDate;        ///< 结束日期，必填
};

//! 管理日志查询应答结构
struct TapAPIManageInfo
{
    TAPIUINT32             MsgID;                              ///< 序列号
    TAPISTR_50             SendFrom;                           ///< 发件人(发件箱编号，短信时为空)
    TAPICHAR               SendManageType;               ///< 发送类型
    TAPISTR_20             AccountNo;           ///< 客户资金账号
    TAPISTR_200            SendAccount;                        ///< 发送账号(手机号或者邮箱)；手机依次取短信电话、开户电话、其他电话；邮箱取账单邮箱

    TAPISTR_200            Title;                              ///< 标题
    TAPISTR_500            Content;                            ///< 正文
    TAPISTR_500            Attachment;                         ///< 附件
    TAPICHAR               SendStatus;                         ///< 发送状态
    TAPISTR_100            Remark;                             ///< 备注
    TAPISTR_100            GUID;                               ///< GUID

    TAPISTR_20             OperatorNo;           ///< 最后操作员编号
    TAPIDATETIME           OperateTime;           ///< 发送时间
};

//! 系统参数查询请求结构
struct TapAPISystemParameterQryReq
{

};

//! 系统参数查询应答结构
struct TapAPISystemParameterInfo
{
    TAPISTR_10        ItemNo;                ///< 项目编号
    TAPISTR_10                ExchangeNo;            ///< 交易所编号
    TAPISTR_10                CommodityNo;        ///< 品种编号
    TAPICommodityType        CommodityType;        ///< 品种类型
    TAPIINT32                ItemValue;            ///< 项目值
    TAPISTR_20                ItemValueStr;        ///< 项目值字符串类型值    
    TAPIREAL64                ItemValueDouble;            ///< 项目值浮点型数据值
};

//! 交易中心前置地址信息查询请求结构
struct TapAPITradeCenterFrontAddressQryReq
{
    TAPISTR_50            FrontAddress;        ///< 前置地址 填空查所有
    TAPISTR_10            FrontPort;            ///< 前置端口 填空查所有
    TAPICHAR                    TradeCenter;                        ///< 交易中心 填空查所有
    TAPICHAR                    IsSSL;                              ///< 是否加密端口
};

//! 交易中心前置地址信息查询应答结构
struct TapAPITradeCenterFrontAddressInfo
{
    TAPISTR_50            FrontName;            ///< 前置名称
    TAPISTR_50            FrontAddress;        ///< 前置地址
    TAPISTR_10            FrontPort;            ///< 前置端口
    TAPICHAR                    TradeCenter;                        ///< 交易中心    
    TAPICHAR            IsEnable;            ///< 是否启用
    TAPICHAR                    IsSSL;                              ///< 是否加密端口
};

#pragma pack(pop)

}

#endif //ES_TRADE_API_STRUCT_H