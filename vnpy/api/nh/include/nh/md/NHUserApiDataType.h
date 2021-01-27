/*************************
*摘要：南华期货交易系统
*文件：NhUserApiDataType.h
*      定义了客户端接口数据类型
*作者：南华期货软件部
*时间：20130604
**************************/

#ifndef __NH_USERAPI_DATATYPE_H__
#define __NH_USERAPI_DATATYPE_H__

enum TE_RESUME_TYPE
{
	TERT_RESTART = 0,
	TERT_RESUME,
	TERT_QUICK
};

/////////////////////////////////////////////////////////////////////////////////
//错误号类型(0-表示成功)，错误号定义参见Protocol_Error.h
typedef int						TErrorCodeType;
//成功
const TErrorCodeType			ERROR_SUCCEED					= 0;
//错误消息类型
typedef char TErrorMessageType[56];

/////////////////////////////////////////////////////////////////////////////////
//日期和时间类型(格式 yyyy-MM-dd hh:nn:ss)
typedef char					TDateTimeType[21];
//日期类型(格式 yyyy-MM-dd)
typedef char					TDateType[11];
//时间类型(格式 hh:nn:ss)
typedef char					TTimeType[11];
//时间列表类型(格式 hh:nn:ss)
typedef char					TTimeListType[512];
//long型时间类型(单位为秒)
typedef long TLongTimeType;

/////////////////////////////////////////////////////////////////////////
///年份类型
typedef int TYearType;

/////////////////////////////////////////////////////////////////////////
///月份类型
typedef int TMonthType;

/////////////////////////////////////////////////////////////////////////
///毫秒类型
typedef int TMillisecType;

////////////////////////////////////////////////////////////////////////////////
//行情数量类型(行情中可能会涉及到股票除权的问题，所以会有小数出现)
typedef double TMdVolumeType;
//数量类型
typedef long TVolumeType;
//价格类型
typedef double TPriceType;
//金额类型
typedef double TMoneyType;
//Int型保留字段类型
typedef int TSaveIntType;
//Double型保留字段类型
typedef double TSaveDoubleType;
//String型保留字段类型
typedef char TSaveStringType[256];
//涨跌幅类型
typedef double TRangeType;
//虚实度类型
typedef double TDeltaType;
//行情来源类型
typedef char TMdSourceType[56];

/////////////////////////////////////////////////////////////////////////////////
//每手合约乘数类型(美国国债是小数,LIFFE小黄金小数)
typedef double					TProductDotType;
//最小变动价分子类型
typedef double					TUpperTickType;
//最小变动价分母类型(非分数报价为1)
typedef int						TLowerTickType;

////////////////////////////////////////////////////////////////////////////////
//登陆机器信息，主要包括mac地址
typedef char					TMachineInfoType[201];
//验证服务器的预留信息
typedef char					TResveredInfoType[256];
//上次登录机器信息
typedef char					TWorkstationInfoType[256];

/////////////////////////////////////////////////////////////////////////
///订阅规则类型
typedef char TRouteKeyType[100][56];

/////////////////////////////////////////////////////////////////////////////////
//Ip地址类型(ipv4最大15位,ipv6最大长度39位)
typedef char					TIpType[41];
/////////////////////////////////////////////////////////////////////////////////
//Mac地址类型
typedef char					TMacAddressType[51];

////////////////////////////////////////////////////////////////////////////////
//序号类型
typedef int TSequenceIDType;
//响应代码代码类型
typedef int TRspCodeType;
//响应文本类型
typedef char TRspStringType[56];

////////////////////////////////////////////////////////////////////////////////
//服务器ID类型
typedef int TServerIDType;
//服务器名称类型
typedef char TServerNameType[56];
//交易所列表类型
typedef char TExchangeListType[256];

/////////////////////////////////////////////////////////////////////////////////
//OMS状态类型
typedef char					TOMSStatusType;
//正常
const TOMSStatusType			OMS_NORMSL						= 'N';
//非工作状态
const TOMSStatusType			OMS_NOT_WORK				= 'D';

////////////////////////////////////////////////////////////////////////////////
//用户名类型
typedef char TUserIDType[56];
//密码类型
typedef char TPassWordType[56];
//动态口令类型
typedef char TOneTimePassWordType[7];
//CA认证数据流类型(放在数据包结尾,通过数据包长度获取数据长度)
typedef char					TCaInfoType[1];
//ca验证信息类型
typedef char TCAInfoType[256];
//验证服务器识别码类型
typedef char TServerCDKeyType[256];
//公钥类型
typedef char TPublicKeyType[129];

////////////////////////////////////////////////////////////////////////////////
//开发者编码类型
typedef char TDevelopCodeType[56];
//开发者授权类型
typedef char TDevelopLicenseType[256];

/////////////////////////////////////////////////////////////////////////////////
//交易帐号类型
typedef char					TTradeNoType[21];
/////////////////////////////////////////////////////////////////////////////////
//客户编号类型
typedef char					TClientNoType[21];
//客户预留信息类型
typedef char					TReservedInfoType[51];
//操作员编号类型
typedef char					TOperatorNoType[11];
//操作员名称类型
typedef char					TOperatorNameType[21];

////////////////////////////////////////////////////////////////////////////////
//是否加密类型
typedef bool TIsEncryptType;
//是
const TIsEncryptType		IS_ENCRYPT_YES		= true;
//否
const TIsEncryptType		IS_ENCRYPT_NO			= false;

/////////////////////////////////////////////////////////////////////////////////
//是否CA认证类型
typedef char					TIsCaLoginType;
//CA认证方式
const TIsCaLoginType			CA_LOGIN						= 'Y';
//非CA认证方式
const TIsCaLoginType			NOT_CA_LOGIN					= 'N';

/////////////////////////////////////////////////////////////////////////////////
//是否强制修改密码类型
typedef char					TIsForcePasswordType;
//强制修改密码
const TIsForcePasswordType		FORCE_PWD						= 'Y';
//非强制修改密码
const TIsForcePasswordType		NOT_FORCE_PWD					= 'N';

/////////////////////////////////////////////////////////////////////////////////
//登录名类型
typedef char					TLoginNoType[21];
//登录名称类型(客户简称,操作员名称)
typedef char					TLoginNameType[21];
//登录密码类型
typedef	char					TLoginPasswordType[21];
//otp密码
typedef char					TOtpPassType[21];

/////////////////////////////////////////////////////////////////////////////////
//密码类型
typedef char					TPasswordTypeType;
//交易密码
const TPasswordTypeType			PASSWORD_TYPE_TRADE				= 'T';
//行情密码
const TPasswordTypeType			PASSWORD_TYPE_QUOTE				= 'Q';
//认证密码
const TPasswordTypeType			PASSWORD_TYPE_AUTH				= 'A';

/////////////////////////////////////////////////////////////////////////////////
//查询通知类型
typedef char					TQryNotifyTypeType;
//所有用户通知
const TQryNotifyTypeType	QRY_NOTIFY_ALL			= 0;
//某个特定用户
const TQryNotifyTypeType	QRY_NOTIFY_SPECIFIC			= 1;

/////////////////////////////////////////////////////////////////////////////////
//市场编号类型
typedef char					TExchangeNoType[11];
//市场名称类型
typedef char					TExchangeNameType[21];

/////////////////////////////////////////////////////////////////////////////////
//市场状态类型
typedef char					TExchangeStateType;
//市场允许交易
const TExchangeStateType		EXCHANGE_STATE_YES				= 'Y';
//市场禁止交易
const TExchangeStateType		EXCHANGE_STATE_NO				= 'N';
//市场只可平仓
const TExchangeStateType		EXCHANGE_STATE_COVER			= 'C';
//市场开盘
const TExchangeStateType		EXCHANGE_STATE_OPEN				= 'O';
//市场处于结算状态
const TExchangeStateType		EXCHANGE_STATE_SETTLE			= 'S';

/////////////////////////////////////////////////////////////////////////////////
//商品编号类型(同一市场内不唯一  市场+商品类型+商品 唯一)
typedef char					TCommodityNoType[11];
//商品名称类型
typedef char					TCommodityNameType[21];

/////////////////////////////////////////////////////////////////////////////////
//商品类型类型
typedef char					TCommodityTypeType;
//现货
const TCommodityTypeType		COMMODITY_TYPE_GOODS			= 'G';
//期货
const TCommodityTypeType		COMMODITY_TYPE_FUTURE			= 'F';
//期权
const TCommodityTypeType		COMMODITY_TYPE_OPTION			= 'O';
//跨期套利
const TCommodityTypeType		COMMODITY_TYPE_SPREAD_MONTH		= 'M';
//跨品种套利
const TCommodityTypeType		COMMODITY_TYPE_SPREAD_COMMODITY	= 'C';

/////////////////////////////////////////////////////////////////////////////////
//商品属性类型
typedef char					TCommodityAttributeType[21];

/////////////////////////////////////////////////////////////////////////////////
//商品状态类型
typedef char					TCommodityStateType;
//商品允许交易
const TCommodityStateType		COMMODITY_STATE_YES				= 'Y';
//商品禁止交易
const TCommodityStateType		COMMODITY_STATE_NO				= 'N';
//商品只可平仓
const TCommodityStateType		COMMODITY_STATE_COVER			= 'C';

/////////////////////////////////////////////////////////////////////////////////
//交割方式类型
typedef char					TDeliveryModeType;
//实物交割
const TDeliveryModeType			DELIVERY_MODE_GOODS				= 'G';
//现金交割
const TDeliveryModeType			DELIVERY_MODE_CASH				= 'C';
//期权行权
const TDeliveryModeType			DELIVERY_MODE_EXECUTE			= 'E';

/////////////////////////////////////////////////////////////////////////////////
//交割日偏移类型(0即等同于最后交易日)
typedef int						TDeliveryDaysType;

/////////////////////////////////////////////////////////////////////////////////
//持仓关键字类型(历史持仓全局唯一,当日持仓每次查询唯一)
typedef int						THoldKeyIdType;
//交割关键字类型(当日交割数据全局唯一)
typedef int						TDeliveryKeyIdType;

/////////////////////////////////////////////////////////////////////////////////
//持仓计算方式
typedef char					TDepositCalculateModeType;
//正常
const TDepositCalculateModeType	DEPOSIT_CALCULATE_MODE_NORMAL	= 'N';
//合约净持仓
const TDepositCalculateModeType	DEPOSIT_CALCULATE_MODE_CLEAN	= 'C';
//品种锁仓
const TDepositCalculateModeType DEPOSIT_CALCULATE_MODE_LOCK		= 'L';

/////////////////////////////////////////////////////////////////////////////////
//合约编号类型
typedef char					TContractNoType[71];
//合约名称类型
typedef char					TContractNameType[21];
//合约到期日天数(合约还有几天到期)
typedef int						TContractLastDays;

/////////////////////////////////////////////////////////////////////////////////
//合约类型类型
typedef char					TContractTypeType;
//单腿合约
const TContractTypeType			CONTRACT_TYPE_SINGLE			= '0';
//跨期套利
const TContractTypeType			CONTRACT_TYPE_SPREAD			= '1';
//互换套利
const TContractTypeType			CONTRACT_TYPE_SWAP				= '2';
//跨品种套利
const TContractTypeType			CONTRACT_TYPE_COMMODITY			= '3';

/////////////////////////////////////////////////////////////////////////////////
//合约状态类型
typedef char					TContractStateType;
//合约允许交易
const TContractStateType		CONTRACT_STATE_YES				= 'Y';
//合约禁止交易
const TContractStateType		CONTRACT_STATE_NO				= 'N';
//合约只可平仓
const TContractStateType		CONTRACT_STATE_COVER			= 'C';


///////////////////////////////////////////////////////////////////////////
//合约交易状态类型
typedef int					TContractTradeStateType;
//合约未知
const TContractTradeStateType		CONTRACT_TRADE_STATE_UNKNOW		= -1;
//开市
const TContractTradeStateType		CONTRACT_TRADE_STATE_OPEN			= 0;
//无红利
const TContractTradeStateType		CONTRACT_TRADE_STATE_NOBONUS		= 1;
//竞价
const TContractTradeStateType		CONTRACT_TRADE_STATE_AUCTION		= 2;
//挂起
const TContractTradeStateType		CONTRACT_TRADE_STATE_HALT			= 3;
//闭市
const TContractTradeStateType		CONTRACT_TRADE_STATE_CLOSE			= 4;
//开市前
const TContractTradeStateType		CONTRACT_TRADE_STATE_BEFORE_OPEN	= 5;
//闭市前
const TContractTradeStateType		CONTRACT_TRADE_STATE_BEFORE_CLOSE	= 6;
//快市
const TContractTradeStateType		CONTRACT_TRADE_STATE_FAST			= 7;


///////////////////////////////////////////////////////////////////////////
//委托编号类型(每个交易服务器内唯一标志,由服务器生成)
typedef int						TOrderIdType;
//本地编号类型(每个交易服务器内唯一标志,由服务器生成)
typedef char					TLocalNoType[21];
//系统编号类型(上级交易所报单唯一标志,不同交易所可能会重复)
typedef char					TSystemNoType[64];
//成交编号
typedef char					TMatchNoType[71];
//本地编号类型(每个交易服务器内唯一标志,由服务器生成)
typedef char					TFeLocalNoType[sizeof(TLocalNoType) + 1];
//成交ID
typedef int					TMatchIdType;

///////////////////////////////////////////////////////////////////////////
//数据流号类型
typedef unsigned int			TStreamIdType;


///////////////////////////////////////////////////////////////////////////
//是否风险报单
typedef char					TIsRiskOrderType;
//是风险报单
const TIsRiskOrderType			RISK_ORDER_YES					= 'Y';
//不是风险报单
const TIsRiskOrderType			RISK_ORDER_NO					= 'N';

///////////////////////////////////////////////////////////////////////////
//买卖类型
typedef char					TDirectType;
//买入
const TDirectType				DIRECT_BUY						= 'B';
//卖出
const TDirectType				DIRECT_SELL						= 'S';

///////////////////////////////////////////////////////////////////////////
//开平类型
typedef char					TOffsetType;
//无
const TOffsetType				OFFSET_NONE						= 'N';
//开仓
const TOffsetType				OFFSET_OPEN						= 'O';
//平仓
const TOffsetType				OFFSET_COVER					= 'C';
//平今
const TOffsetType				OFFSET_COVER_TODAY				= 'T';

/////////////////////////////////////////////////////////////////////////////////
//平仓方式类型
typedef char					TCoverModeType;
//不区分开平
const TCoverModeType			COVER_MODE_NONE					= 'N';
//平仓未了结
const TCoverModeType			COVER_MODE_UNFINISHED			= 'U';
//开仓和平仓
const TCoverModeType			COVER_MODE_OPENCOVER			= 'C';
//开仓、平仓和平今
const TCoverModeType			COVER_MODE_COVERTODAY			= 'T';

///////////////////////////////////////////////////////////////////////////
//投机保值类型
typedef char					THedgeType;
//无
const THedgeType				HEDGE_NONE						= 'N';
//投机
const THedgeType				HEDGE_T							= 'T';
//保值
const THedgeType				HEDGE_B							= 'B';

///////////////////////////////////////////////////////////////////////////
//人工填写手续费
typedef char					TManualFeeType;
//人工
const TManualFeeType			MANUALFEE_YES					= 'Y';
//自动
const TManualFeeType			MANUALFEE_NO					= 'N';


///////////////////////////////////////////////////////////////////////////
//委托类型
typedef char					TOrderTypeType;
//限价
const TOrderTypeType			ORDER_TYPE_LIMIT				= '1';
//市价
const TOrderTypeType			ORDER_TYPE_MARKET				= '2';
//限价止损
const TOrderTypeType			ORDER_TYPE_STOP_LIMIT			= '3';
//市价止损
const TOrderTypeType			ORDER_TYPE_STOP_MARKET			= '4';

///////////////////////////////////////////////////////////////////////////
//委托方式
typedef char					TOrderWayType;
//自助电子单
const char						ORDER_WAY_SELF_ETRADER			= 'E';
//代理电子单
const char						ORDER_WAY_PROXY_ETRADER			= 'P';
//外部电子单(外部电子系统下单，本系统录入)
const char						ORDER_WAY_JTRADER				= 'J';
//人工录入单(外部其他方式下单，本系统录入)
const char						ORDER_WAY_MANUAL				= 'M';
//carry单
const char						ORDER_WAY_CARRY					= 'C';
//程式化报单
const char						ORDER_WAY_PROGRAM				= 'S';

///////////////////////////////////////////////////////////////////////////
//委托模式类型
typedef char					TOrderModeType;
//FOK
const TOrderModeType			ORDER_MODE_FOK					= '1';
//FAK或IOC
const TOrderModeType			ORDER_MODE_FAK					= '2';
//当日有效
const TOrderModeType			ORDER_MODE_GFD					= '3';
//取消前有效
const TOrderModeType			ORDER_MODE_GTC					= '4';
//指定日期前有效
const TOrderModeType			ORDER_MODE_GTD					= '5';

///////////////////////////////////////////////////////////////////////////
//委托录入类型
typedef char					TOrderInputType;
//是
const TOrderInputType			ORDER_INPUT_YES					= 'Y';
//否
const TOrderInputType			ORDER_INPUT_NO					= 'N';

///////////////////////////////////////////////////////////////////////////
//委托状态类型
typedef char					TOrderStateType;
//指令失败
const TOrderStateType			ORDER_STATE_FAIL				= '0';
//已受理
const TOrderStateType			ORDER_STATE_ACCEPT				= '1';
//已挂起
const TOrderStateType			ORDER_STATE_SUPPENDED			= '2';
//已排队
const TOrderStateType			ORDER_STATE_QUEUED				= '3';
//待撤消(排队临时状态)
const TOrderStateType			ORDER_STATE_DELETEING			= '4';
//待修改(排队临时状态)
const TOrderStateType			ORDER_STATE_MODIFYING			= '5';
//部分撤单
const TOrderStateType			ORDER_STATE_PARTDELETED			= '6';
//完全撤单
const TOrderStateType			ORDER_STATE_DELETED				= '7';
//部分成交
const TOrderStateType			ORDER_STATE_PARTFINISHED		= '8';
//完全成交
const TOrderStateType			ORDER_STATE_FINISHED			= '9';

///////////////////////////////////////////////////////////////////////////
//委托成交删除标记
typedef char					TDeletedType;
//是
const TDeletedType				DEL_YES							= 'Y';
//否
const TDeletedType				DEL_NO							= 'N';
//隐藏
const TDeletedType				DEL_DISAPPEAR					= 'D';

///////////////////////////////////////////////////////////////////////////
//成交方式
typedef char					TMatchWayType;
//所有
const char						MATCH_WAY_ALL					= 'A';
//自助电子单
const char						MATCH_WAY_SELF_ETRADER			= 'E';
//代理电子单
const char						MATCH_WAY_PROXY_ETRADER			= 'P';
//外部电子单(外部电子系统下单，本系统录入)
const char						MATCH_WAY_JTRADER				= 'J';
//人工录入单(外部其他方式下单，本系统录入)
const char						MATCH_WAY_MANUAL				= 'M';
//carry单
const char						MATCH_WAY_CARRY					= 'C';
//交割单
const char						MATCH_WAY_DELIVERY				= 'D';
//程式化单
const char						MATCH_WAY_PROGRAM				= 'S';

///////////////////////////////////////////////////////////////////////////
//成交方式类型
typedef char					TMatchModeType;
//正常
const TMatchModeType			MATCH_MODE_NORMAL				= 'N';
//更新委托
const TMatchModeType			MATCH_MODE_UPDATE				= 'U';
//其他
const TMatchModeType			MATCH_MODE_OTHER				= 'O';

///////////////////////////////////////////////////////////////////////////
//T+1成交
typedef char					TAddOneType;
//T+1成交
const TAddOneType				ADD_ONE_YES						= 'Y';
//非T+1成交
const TAddOneType				ADD_ONE_NO						= 'N';



//////////////////////////资金//////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//货币编号类型
typedef char					TCurrencyNoType[11];
//货币名称类型
typedef char					TCurrencyNameType[21];

/////////////////////////////////////////////////////////////////////////////////
//是否基币类型
typedef char					TIsPrimaryCurrencyType;
//是基币
const TIsPrimaryCurrencyType	CURRENCY_PRIMARY_YES			= 'Y';
//不是基币
const TIsPrimaryCurrencyType	CURRENCY_PRIMARY_NO			= 'N';

/////////////////////////////////////////////////////////////////////////////////
//是否与其他币种共享计算(共享表示非当前币种交易品种也可以占用当前币种资金进行交易)
typedef char					TIsShareCurrencyType;
//共享计算币种
const TIsShareCurrencyType		CURRENCY_SHARE_YES				= 'Y';
//非共享计算币种
const TIsShareCurrencyType		CURRENCY_SHARE_NO				= 'N';

/////////////////////////////////////////////////////////////////////////////////
//汇率(1当前货币换算多少基币)
typedef double					TExchangeRateType;

/////////////////////////////////////////////////////////////////////////////////
//是否包含合计值
typedef char					TContainTotleType;
//包含
const TContainTotleType			ContainTotle_Yes			= 'Y';
//不包含
const TContainTotleType			ContainTotle_No				= 'N';

///////////////////////////////////////////////////////////////////////////
//银行标识
typedef char					TBankType[3];
//银行名称
typedef char					TBankNameType[21];
//银行账号
typedef char					TAccountType[51];

///////////////////////////////////////////////////////////////////////////
//本外币标识
typedef char					TLWFlagType;
//境内人民币账户
const TLWFlagType				LWFlag_L						= 'L';
//客户境内外币账户
const TLWFlagType				LWFlag_W						= 'W';
//公司境内外币账户
const TLWFlagType				LJFFlag_J						= 'J';
//公司境外外币账户
const TLWFlagType				LJFFlag_F						= 'F';

///////////////////////////////////////////////////////////////////////////
//保证金计算方式
typedef char					TDepositModeType;
//比例
const TDepositModeType			DEPOSIT_MODE_B					= '1';
//定额
const TDepositModeType			DEPOSIT_MODE_D					= '2';
//差值比例
const TDepositModeType			DEPOSIT_MODE_CB					= '3';
//差值定额
const TDepositModeType			DEPOSIT_MODE_CD					= '4';
//折扣
const TDepositModeType			DEPOSIT_MODE_Z					= '5';

///////////////////////////////////////////////////////////////////////////
//出入金流水号类型
typedef int						TCashSerialIdType;
//资金调整流水号类型
typedef int						TAdjustSerialIdType;

///////////////////////////////////////////////////////////////////////////
//出入金类型
typedef char					TCashTypeType;
//出金
const TCashTypeType				CASH_TYPE_OUT					= 'O';
//入金
const TCashTypeType				CASH_TYPE_IN					= 'I';

//出入金状态
typedef char					TCashStateType;
//未审核
const TCashStateType			CASH_STATE_NOT_CHECK			= 'N';
//已审核
const TCashStateType			CASH_STATE_CHECK				= 'Y';
//审核未通过
const TCashStateType			CASH_STATE_FAIL					= 'F';

///////////////////////////////////////////////////////////////////////////
//出入金方式
typedef char					TCashModeType;
//转账
const TCashModeType				CASH_MODE_A						= 'A';
//支票
const TCashModeType				CASH_MODE_B						= 'B';
//现金
const TCashModeType				CASH_MODE_C						= 'C';
//换汇
const TCashModeType				CASH_MODE_E						= 'E';

///////////////////////////////////////////////////////////////////////////
//出入金备注
typedef char					TCashRemarkType[101];

//资金调整状态
typedef char					TAdjustStateType;
//未审核
const TAdjustStateType			ADJUST_STATE_NOT_CHECK			= 'N';
//已审核
const TAdjustStateType			ADJUST_STATE_CHECK				= 'Y';
//审核未通过
const TAdjustStateType			ADJUST_STATE_FAIL				= 'F';

///////////////////////////////////////////////////////////////////////////
//资金调整类型类型
typedef char					TAdjustTypeType;

///////////////////////////////////////////////////////////////////////////
//资金变化字段类型(从低位到高位,每位对应一个变化字段)
typedef unsigned int			TMoneyChgType;
//资金调整                                                                 
const TMoneyChgType				MONEY_CHG_ADJUST				= 0x00000001;
//入金                                                                     
const TMoneyChgType				MONEY_CHG_CASHIN				= 0x00000002;
//出金                                                                     
const TMoneyChgType				MONEY_CHG_CASHOUT   			= 0x00000004;
//手续费                                                                   
const TMoneyChgType				MONEY_CHG_FEE					= 0x00000008;
//冻结资金                                                                 
const TMoneyChgType				MONEY_CHG_FROZEN				= 0x00000010;
//逐笔平盈                                                                 
const TMoneyChgType				MONEY_CHG_COVERPROFIT			= 0x00000020;
//盯市平盈                                                                 
const TMoneyChgType				MONEY_CHG_DAYCVERPROFIT		= 0x00000040;
//逐笔浮盈                                                                 
const TMoneyChgType				MONEY_CHG_FLOATPROFIT			= 0x00000080;
//盯市浮盈                                                                 
const TMoneyChgType				MONEY_CHG_DAYFLOATPROFIT		= 0x00000100;
//未结平盈                                                                 
const TMoneyChgType				MONEY_CHG_UNEXPIREDPROFIT		= 0x00000200;
//权利金                                                                   
const TMoneyChgType				MONEY_CHG_PREMIUM				= 0x00000400;
//保证金                                                                   
const TMoneyChgType				MONEY_CHG_DEPOSIT				= 0x00000800;
//维持保证金                                                               
const TMoneyChgType				MONEY_CHG_KEEPDEPOSIT			= 0x00001000;
//质押资金                                                                 
const TMoneyChgType				MONEY_CHG_PLEDGE				= 0x00002000;
//可用资金                                                                 
const TMoneyChgType				MONEY_CHG_TAVAILABLE			= 0x00004000;

#endif
