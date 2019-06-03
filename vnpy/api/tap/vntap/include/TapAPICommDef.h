#ifndef TAP_API_COMM_DEF_H
#define TAP_API_COMM_DEF_H

#pragma pack(push, 1)

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_CHARS	基本字符串类型定义
 *	@{
 */
//=============================================================================

//! 长度为10的字符串
typedef char	TAPISTR_10[11];
//! 长度为20的字符串
typedef char	TAPISTR_20[21];
//! 长度为30的字符串
typedef char	TAPISTR_30[31];
//! 长度为40的字符串
typedef char	TAPISTR_40[41];
//! 长度为50的字符串
typedef char	TAPISTR_50[51];
//! 长度为70的字符串
typedef char	TAPISTR_70[71];
//! 长度为100的字符串
typedef char	TAPISTR_100[101];
//! 长度为300的字符串
typedef char	TAPISTR_300[301];
//! 长度为500的字符串
typedef char	TAPISTR_500[501];
//! 长度为2000的字符串
typedef char	TAPISTR_2000[2001];

//! Authorization Code
typedef char	TAPIAUTHCODE[513];


//! 单字符定义，可用于定义其他类型
typedef char				TAPICHAR;
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_NUMBER	基本数值类型定义
 *	@{
 */
//=============================================================================

//! int 32
typedef int					TAPIINT32;
//! unsigned 32
typedef unsigned int		TAPIUINT32;
//! int 64
typedef long long			TAPIINT64;
//! unsigned 64
typedef unsigned long long	TAPIUINT64;
//! unsigned 16
typedef unsigned short		TAPIUINT16;
//! unsigned 8
typedef unsigned char		TAPIUINT8;
//! real 64
typedef double				TAPIREAL64;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_YNFLAG	是否标示
 *	@{
 */
//=============================================================================
//! 是否标示
typedef TAPICHAR			TAPIYNFLAG;
//! 是
const TAPIYNFLAG			APIYNFLAG_YES	='Y';
//! 否
const TAPIYNFLAG			APIYNFLAG_NO	='N';

/** @}*/



//=============================================================================
/**
 *	\addtogroup G_DATATYPE_DATETIME	日期时间类型定义
 *	@{
 */
//=============================================================================

//! 时间戳类型(格式 yyyy-MM-dd hh:nn:ss.xxx)
typedef char	TAPIDTSTAMP[24];
//! 日期和时间类型(格式 yyyy-MM-dd hh:nn:ss)
typedef char	TAPIDATETIME[20];
//! 日期类型(格式 yyyy-MM-dd)
typedef char	TAPIDATE[11];
//! 时间类型(格式 hh:nn:ss)
typedef char	TAPITIME[9];
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_LOG_LEVEL	日志级别
 *	@{
 */
//=============================================================================
//! 日志级别
typedef TAPICHAR			TAPILOGLEVEL;
//! 无
const TAPILOGLEVEL			APILOGLEVEL_NONE	='N';
//! Error
const TAPILOGLEVEL			APILOGLEVEL_ERROR	='E';
//! Warning
const TAPILOGLEVEL			APILOGLEVEL_WARNING	='W';
//! Debug
const TAPILOGLEVEL			APILOGLEVEL_DEBUG	='D';
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_COMMODITY_TYPE	品种类型
 *	@{
 */
//=============================================================================

//! 品种类型
typedef TAPICHAR               TAPICommodityType;
//! 无
const TAPICommodityType		TAPI_COMMODITY_TYPE_NONE				= 'N';
//! 现货
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPOT				= 'P';
//! 期货
const TAPICommodityType		TAPI_COMMODITY_TYPE_FUTURES				= 'F';
//! 期权
const TAPICommodityType		TAPI_COMMODITY_TYPE_OPTION				= 'O';
//! 跨期套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPREAD_MONTH		= 'S';
//! 跨品种套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPREAD_COMMODITY	= 'M';
//! 看涨垂直套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_BUL					= 'U';
//! 看跌垂直套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_BER					= 'E';
//! 跨式套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_STD					= 'D';
//! 宽跨式套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_STG					= 'G';
//! 备兑组合
const TAPICommodityType		TAPI_COMMODITY_TYPE_PRT					= 'R';
//! 看涨水平期权
const TAPICommodityType		TAPI_COMMODITY_TYPE_BLT		    		= 'L';
//! 看跌水平期权
const TAPICommodityType		TAPI_COMMODITY_TYPE_BRT		    		= 'Q';
//! 外汇——直接汇率
const TAPICommodityType		TAPI_COMMODITY_TYPE_DIRECTFOREX			= 'X';
//! 外汇——间接汇率
const TAPICommodityType		TAPI_COMMODITY_TYPE_INDIRECTFOREX		= 'I';
//! 外汇——交叉汇率
const TAPICommodityType		TAPI_COMMODITY_TYPE_CROSSFOREX			= 'C';
//! 指数
const TAPICommodityType		TAPI_COMMODITY_TYPE_INDEX				= 'Z';
//! 股票
const TAPICommodityType		TAPI_COMMODITY_TYPE_STOCK				= 'T';
//! 现货延期
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPOT_TRADINGDEFER   = 'Y';
//! 中金所对锁组合
const TAPICommodityType		TAPI_COMMODITY_TYPE_FUTURE_LOCK	    	= 'J';
//! 中金所EFP
const TAPICommodityType		TAPI_COMMODITY_TYPE_EFP			    	= 'A';

/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_CALL_OR_PUT	看涨看跌标示
 *	@{
 */
//=============================================================================

//! 看涨看跌标示
typedef TAPICHAR			TAPICallOrPutFlagType;
//! 买权
const TAPICallOrPutFlagType		TAPI_CALLPUT_FLAG_CALL				= 'C';
//! 卖权
const TAPICallOrPutFlagType		TAPI_CALLPUT_FLAG_PUT				= 'P';
//! 无
const TAPICallOrPutFlagType		TAPI_CALLPUT_FLAG_NONE				= 'N';

/** @}*/


//! Application信息
struct TapAPIApplicationInfo
{
	TAPIAUTHCODE            AuthCode;								///< 授权码
	TAPISTR_300				KeyOperationLogPath;					///< 关键操作日志路径
};


//! 品种编码结构
struct TapAPICommodity
{
	TAPISTR_10              ExchangeNo;                             ///< 交易所编码
	TAPICommodityType		CommodityType;                          ///< 品种类型
	TAPISTR_10				CommodityNo;                            ///< 品种编号
};

//! 合约编码结构
struct TapAPIContract
{
	TapAPICommodity			Commodity;								///< 品种
	TAPISTR_10				ContractNo1;                            ///< 合约代码1
	TAPISTR_10				StrikePrice1;                           ///< 执行价1
	TAPICallOrPutFlagType	CallOrPutFlag1;                         ///< 看涨看跌标示1
	TAPISTR_10				ContractNo2;                            ///< 合约代码2
	TAPISTR_10				StrikePrice2;                           ///< 执行价2
	TAPICallOrPutFlagType	CallOrPutFlag2;                         ///< 看涨看跌标示2
};

//! 交易所信息
struct TapAPIExchangeInfo
{
	TAPISTR_10				ExchangeNo;								///< 交易所编码
	TAPISTR_20				ExchangeName;							///< 交易所名称
};

//! 修改密码请求
struct TapAPIChangePasswordReq
{
	TAPISTR_20				OldPassword;							///< 旧密码
	TAPISTR_20				NewPassword;							///< 新密码
};

#pragma pack(pop)

#endif