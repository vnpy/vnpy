#ifndef TAP_QUOTE_API_DATA_TYPE_H
#define TAP_QUOTE_API_DATA_TYPE_H
//该文件定义了TapQuoteAPI 使用的数据类型和数据结构

#include "TapAPICommDef.h"

#pragma pack(push, 1)

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_Q_BASIC	行情基本类型
 *	@{
 */
//=============================================================================

//! 行情价格
typedef TAPIREAL64		TAPIQPRICE;
//! 行情量
typedef TAPIUINT64		TAPIQVOLUME;
//! 变化值
typedef TAPIINT64		TAPIQDIFF;	

/** @}*/


//=============================================================================
/**
 *	\addtogroup G_STRUCT_Q	行情结构体定义
 *	@{
 */
//=============================================================================

//! 登录认证信息
struct TapAPIQuoteLoginAuth
{
	TAPISTR_20			UserNo;					///< 用户名
	TAPIYNFLAG			ISModifyPassword;		///< 是否修改密码，'Y'表示是，'N'表示否
	TAPISTR_20			Password;				///< 用户密码
	TAPISTR_20			NewPassword;			///< 新密码，如果设置了修改密码则需要填写此字段
	TAPISTR_20			QuoteTempPassword;		///< 行情临时密码
	TAPIYNFLAG			ISDDA;					///< 是否需呀动态认证，'Y'表示是，'N'表示否
	TAPISTR_30			DDASerialNo;			///< 动态认证码
};

//! 登录反馈信息
struct TapAPIQuotLoginRspInfo
{
	TAPISTR_20					UserNo;							///< 用户名
	TAPIINT32					UserType;						///< 用户类型
	TAPISTR_20					UserName;						///< 昵称，GBK编码格式
	TAPISTR_20					QuoteTempPassword;				///< 行情临时密码
	TAPISTR_50					ReservedInfo;					///< 用户自己设置的预留信息
	TAPISTR_40					LastLoginIP;					///< 上次登录的地址
	TAPIUINT32					LastLoginProt;					///< 上次登录使用的端口
	TAPIDATETIME				LastLoginTime;					///< 上次登录的时间
	TAPIDATETIME				LastLogoutTime;					///< 上次退出的时间
	TAPIDATE					TradeDate;						///< 当前交易日期
	TAPIDATETIME				LastSettleTime;					///< 上次结算时间
	TAPIDATETIME				StartTime;						///< 系统启动时间
	TAPIDATETIME				InitTime;						///< 系统初始化时间
};


//! 品种信息
struct TapAPIQuoteCommodityInfo
{
	TapAPICommodity			Commodity;							///< 品种
	TAPISTR_20				CommodityName;						///< 品种名称,GBK编码格式
	TAPISTR_30				CommodityEngName;					///< 品种英文名称
	TAPIREAL64				ContractSize;						///< 每手乘数
	TAPIREAL64				CommodityTickSize;					///< 最小变动价位
	TAPIINT32				CommodityDenominator;				///< 报价分母
	TAPICHAR                CmbDirect;							///< 组合方向
	TAPIINT32				CommodityContractLen;				///< 品种合约年限
	TAPIYNFLAG				IsDST;								///< 是否夏令时,'Y'为是,'N'为否
	TapAPICommodity			RelateCommodity1;					///< 关联品种1
	TapAPICommodity			RelateCommodity2;					///< 关联品种2
};


//! 行情合约信息
struct TapAPIQuoteContractInfo
{
	TapAPIContract				Contract;							///< 合约
	TAPICHAR					ContractType;                       ///< 合约类型,'1'表示交易行情合约,'2'表示行情合约
	TAPISTR_10					QuoteUnderlyingContract;			///< 行情真实合约
	TAPISTR_70					ContractName;                       ///< 合约名称
	TAPIDATE					ContractExpDate;                    ///< 合约到期日	
	TAPIDATE					LastTradeDate;                      ///< 最后交易日
	TAPIDATE					FirstNoticeDate;                    ///< 首次通知日
};

//! 行情全文
struct TapAPIQuoteWhole
{
	TapAPIContract				Contract;						///< 合约
	TAPISTR_10					CurrencyNo;						///< 币种编号
	TAPICHAR					TradingState;					///< 交易状态。1,集合竞价;2,集合竞价撮合;3,连续交易;4,交易暂停;5,闭市
	TAPIDTSTAMP					DateTimeStamp;					///< 时间戳
	TAPIQPRICE					QPreClosingPrice;				///< 昨收盘价
	TAPIQPRICE					QPreSettlePrice;				///< 昨结算价
	TAPIQVOLUME					QPrePositionQty;				///< 昨持仓量
	TAPIQPRICE					QOpeningPrice;					///< 开盘价
	TAPIQPRICE					QLastPrice;						///< 最新价
	TAPIQPRICE					QHighPrice;						///< 最高价
	TAPIQPRICE					QLowPrice;						///< 最低价
	TAPIQPRICE					QHisHighPrice;					///< 历史最高价
	TAPIQPRICE					QHisLowPrice;					///< 历史最低价
	TAPIQPRICE					QLimitUpPrice;					///< 涨停价
	TAPIQPRICE					QLimitDownPrice;				///< 跌停价
	TAPIQVOLUME					QTotalQty;						///< 当日总成交量
	TAPIQPRICE					QTotalTurnover;					///< 当日成交金额
	TAPIQVOLUME					QPositionQty;					///< 持仓量
	TAPIQPRICE					QAveragePrice;					///< 均价
	TAPIQPRICE					QClosingPrice;					///< 收盘价
	TAPIQPRICE					QSettlePrice;					///< 结算价
	TAPIQVOLUME					QLastQty;						///< 最新成交量
	TAPIQPRICE					QBidPrice[20];					///< 买价1-20档
	TAPIQVOLUME					QBidQty[20];					///< 买量1-20档
	TAPIQPRICE					QAskPrice[20];					///< 卖价1-20档
	TAPIQVOLUME					QAskQty[20];					///< 卖量1-20档
	TAPIQPRICE					QImpliedBidPrice;				///< 隐含买价
	TAPIQVOLUME					QImpliedBidQty;					///< 隐含买量
	TAPIQPRICE					QImpliedAskPrice;				///< 隐含卖价
	TAPIQVOLUME					QImpliedAskQty;					///< 隐含卖量
	TAPIQPRICE					QPreDelta;						///< 昨虚实度
	TAPIQPRICE					QCurrDelta;						///< 今虚实度
	TAPIQVOLUME					QInsideQty;						///< 内盘量
	TAPIQVOLUME					QOutsideQty;					///< 外盘量
	TAPIQPRICE					QTurnoverRate;					///< 换手率
	TAPIQVOLUME					Q5DAvgQty;						///< 五日均量
	TAPIQPRICE					QPERatio;						///< 市盈率
	TAPIQPRICE					QTotalValue;					///< 总市值
	TAPIQPRICE					QNegotiableValue;				///< 流通市值
	TAPIQDIFF					QPositionTrend;					///< 持仓走势
	TAPIQPRICE					QChangeSpeed;					///< 涨速
	TAPIQPRICE					QChangeRate;					///< 涨幅
	TAPIQPRICE					QChangeValue;					///< 涨跌值
	TAPIQPRICE					QSwing;							///< 振幅
	TAPIQVOLUME					QTotalBidQty;					///< 委买总量
	TAPIQVOLUME					QTotalAskQty;					///< 委卖总量
	TapAPIContract				UnderlyContract;				///< 虚拟合约对应的真实合约
};


/** @}*/





#pragma pack(pop)

#endif