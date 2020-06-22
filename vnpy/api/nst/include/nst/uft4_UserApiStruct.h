#ifndef _UFT4_APIDATASTRUCT_H_
#define _UFT4_APIDATASTRUCT_H_

#include "os_common.h"
#include "uft4_UserApiDataType.h"


typedef enum tagExchange_Type
{
	EXCHANGE_CFFEX = 0,	//中金所
	EXCHANGE_SHFE,		//1上期所
	EXCHANGE_DCE,		//2大商所
	EXCHANGE_SSEOPT,	//3上证期权
	EXCHANGE_CZCE,		//4
	EXCHANGE_SZSE,		//5深圳证券
	EXCHANGE_SSE,		//6上海证券
	EXCHANGE_UNKNOWN,
}E_EXCHANGE_TYPE;

typedef struct tagUftFtdcInputOrderField
{
	///报单编号
	T_UFT_FtdcOrderSysIDType	OrderSysID;
	///会员代码
	T_UFT_FtdcParticipantIDType	ParticipantID;
	///客户代码
	T_UFT_FtdcClientIDType	ClientID;
	///交易用户代码
	T_UFT_FtdcUserIDType	UserID;
	///合约代码
	T_UFT_FtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	T_UFT_FtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	T_UFT_FtdcDirectionType	Direction;
	///组合开平标志
	T_UFT_FtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	T_UFT_FtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	T_UFT_FtdcPriceType	LimitPrice;
	///数量
	T_UFT_FtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	T_UFT_FtdcTimeConditionType	TimeCondition;
	///GTD日期
	T_UFT_FtdcDateType	GTDDate;
	///成交量类型
	T_UFT_FtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	T_UFT_FtdcVolumeType	MinVolume;
	///触发条件
	T_UFT_FtdcContingentConditionType	ContingentCondition;
	///止损价
	T_UFT_FtdcPriceType	StopPrice;
	///强平原因
	T_UFT_FtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	T_UFT_FtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	T_UFT_FtdcBoolType	IsAutoSuspend;
	///业务单元
	T_UFT_FtdcBusinessUnitType	BusinessUnit;

}CUftFtdcInputOrderField;




// 客户持仓表
typedef struct tagUftQryInvestorPositionField
{
	char		futu_code[7];		//	合约代码	HsFuturesCode;通过CFutuCode.Get获取
	char		entrust_bs;			//	买卖方向	HsType：‘0’买；‘1’卖
	int32_t		OldEnableAmount;	//	老仓可用数量	HsQuantity
	int32_t		OldCurrentAmount;	//	老仓持仓数量	HsQuantity
	int32_t		TodayEnableAmount;//	当日可用数量	HsQuantity
	int32_t		TodayCurrentAmount;//	当日持仓数量	HsQuantity
	T_UFT_FtdcMoneyType	OldOpenBalance;	//	老仓持仓成交额	HsAmount
	T_UFT_FtdcMoneyType	TodayOpenBalance;	//	今仓持仓成交额	HsAmount
	T_UFT_FtdcMoneyType	HoldMargin;		//	持仓保证金	HsAmount
} QryInvestorPositionField;

// 报单录入请求
typedef struct tagUftReqOrderInsertField
{
	CUftFtdcInputOrderField	Order;
	int64_t						OrderRef;		//第三方标识
	uint8_t                     MaginCheck;//用于是否进行大边优惠‘0’不检查是否优惠，‘1’检查
} CUftReqOrderInsertField;


//报单柜台响应
typedef struct tagUftAnsOrderInsertField
{
	int64_t						OrderRef;		//第三方标识
	uint32_t					OrderIndex;		//报单编号
	uint32_t					ProcessTime;	// 委托处理时间
	uint32_t					TotalTime;		// 发送应答时间
	uint32_t					ExchangeTime;	// 交易所时间
	uint32_t					SenderID;
	uint32_t					LocalTimeDelay; //本地网络延时
	char                        StockCode[8];
	char						Direction;
	char						EntrustType;
	double						Price;
	int32_t						Amount;
} CUftAnsOrderInsertField;

//报单交易所响应
typedef struct tagUftRspnOrderInsertField
{
	int64_t						OrderRef;		//第三方标识
	uint32_t					OrderIndex;     //返回原报单的OrderIndex
	uint32_t					ProcessTime;	// 委托处理时间
	uint32_t					TotalTime;		// 发送应答时间
	uint32_t					ExchangeTime;	// 交易所时间
	T_UFT_FtdcOrderSysIDType	OrderSysID;		//交易所报单编号
	char						OrderStatus;	//报单状态
	
} CUftRspnOrderInsertField;//API EXPOSURE




typedef struct tagUftAnsOrderActionField
{
	int64_t						OrderRef;		//第三方标识
	uint32_t					OrderIndex;
	T_UFT_FtdcOrderSysIDType	OrderSysID;		//报单编号
	T_UFT_FtdcOrderLocalIDType	OrderLocalID;	//本地报单编号
	uint32_t					SenderID;
} CUftAnsOrderActionField;



//撤单操作
typedef struct tagUftRspnOrderActionField
{
	T_UFT_FtdcOrderSysIDType		OrderSysID;		//报单编号
	T_UFT_FtdcOrderLocalIDType	OrderLocalID;	//本地报单编号
	int64_t						OrderRef;		//第三方标识
	uint32_t					OrderIndex;	
} CUftRspnOrderActionField;



//报单回报
typedef struct tagUftRtnnOrderField
{
	int64_t						OrderRef;		//第三方标识
	uint32_t					OrderIndex;     //报单编号
	uint32_t					ProcessTime;	// 委托处理时间
	uint32_t					TotalTime;		// 发送应答时间
	uint32_t					ExchangeTime;	// 交易所时间
	T_UFT_FtdcOrderSysIDType	OrderSysID;		//交易所报单编号
	T_UFT_FtdcVolumeType		VolumeTotal;	//剩余数量
	T_UFT_FtdcOrderStatusType	OrderStatus;	//报单状态
	char                        StockCode[8];
	char						EntrustType;
	char						Direction;
	double						Price;
	int32_t						Amount;
} CUftRtnnOrderField;



//成交回报
typedef struct tagUftRtnnTradeField
{
	T_UFT_FtdcPriceType				BusinessPrice;		// 成交价格	HsFutuPrice
	int32_t							BusinessTime;		// 成交时间	HsTime
	int32_t							BusinessAmount;		// 成交数量	HsQuantity
	double							fare;				// 手续费
	int64_t							OrderRef;			//第三方标识
	uint32_t						OrderIndex;			// 报单本地标识
	T_UFT_FtdcTradeIDType			BusinessId;		// 成交编号	
	T_UFT_FtdcOrderSysIDType 		OrderSysID;			// 报单编号，char[13], 这里未对齐
	int8_t							session_id;		//会话ID
	char						    Direction;          //买卖标志
	char						    OffsetFlag;         //开平标志
	char						    HedgeFlag;			//投机套保标志
	int8_t            			    reserve[5];			//占位
	char							InstrumentID[17];     //合约号	
	char							StockCode[9];
} CUftRtnnTradeField;


//资金查询应答
typedef struct tagUftAnsQueryFundField
{
	T_UFT_FtdcMoneyType			EnabledBalance;	//可用资金
	T_UFT_FtdcMoneyType			Deposit;		//当日入金
	T_UFT_FtdcMoneyType			BeginBalance;	// 初始权益
	T_UFT_FtdcMoneyType			Margin;			// 保证金
	T_UFT_FtdcMoneyType			Profit;			//平仓盈亏
	double						TotalFare;		//手续费
	double						CurrBalance;	// 当前权益
	double						floating_gain_loss; //持仓盈亏
	double						FrozenBalance;	// 冻结资金
	uint32_t					SenderID;
	double						EnablePurQuota;	// 可用限购额度
} CUftAnsQueryFundField;


//委托查询
typedef struct tagUftReqQueryOrderField
{
	T_UFT_FtdcInstrumentIDType	InstrumentID;	//合约代码；InstrumentID[0]为'\0'表示查所有
	int32_t						BeginTime;		//委托起始时间；为0表示不限制
	int32_t						EndTime;		//委托终止时间；为0或小于BeginTime表示不限制
	T_UFT_FtdcOrderSysIDType		OrderSysID;		//交易所报单编号；为OrderSysID[0]为'\0'表示不限制
	uint32_t					OrderIndex;		//本地报单索引；为0xFFFFFFFF表示不限制
	uint32_t					EntrustSenderID;//客户端报单编号；为0xFFFFFFFF表示不限制
	int64_t						OrderRef;		//客户端第三方标识；为-1表示不限制
	uint32_t					Position;		//定位串，用于指定分页获取该记录号及之后的记录；首次输入0；后续使用应答中的Position值
	uint8_t						all_session_data;//为1表示获取所有会话的数据		

} CUftReqQueryOrderField;

//委托查询应答
typedef struct tagUftAnsQueryOrderField
{
	
	CUftFtdcInputOrderField	    Order;
	int64_t						OrderRef;		//第三方标识
	char						MaginCheck;		// 是否进行大边优惠‘0’不检查是否优惠，‘1’检查
	int32_t						VolumeTotal;	//委托剩余数量
	char						OrderStatus;	// 订单状态：待报，已报，部成，成交，废单
	int8_t						session_id;		//会话ID
	int8_t            			reserve;		//占位
	int32_t						OrderTime;		// 委托时间
	uint32_t					SenderID;
	int32_t						ErrorID;
	uint32_t					OrderIndex;
	//证券NST
	char						StockCode[8];   //股票代码，无\0结束符，不足以空格补齐
	char						Direction;      //买卖标志1买；2卖
	char						EntrustType;    //委托类型'0'限价委托；'1'本方最优；'2'对手方最优剩余转限价；'3'市价立即成交剩余撤销；'4'市价全额成交或撤销；'5'市价最优五档全额成交剩余撤销
	char						CashMargin;		//信用标识1=Cash，普通交易；2=Open ，融资券开仓；3=Close ，融资券平仓
	int8_t						TGWNo;			//交易所网关编号，0轮流，1~n指定范围为指定网关报单
	double						Price;			//委托价格N13(4)
	double						Amount;			//委托数量N15(2)
	char						OrderSysID[17]; //交易所订单编号
	char						ClOrdID[11];	//本地单号 无\0结束符
} CUftAnsQueryOrderField;

//成交查询
typedef struct tagUftReqQueryTradeField
{
	T_UFT_FtdcInstrumentIDType	InstrumentID;	//合约代码；InstrumentID[0]为'\0'表示查所有
	int32_t						BeginTime;		//成交起始时间；为0表示不限制
	int32_t						EndTime;		//成交终止时间；为0或小于BeginTime表示不限制
	T_UFT_FtdcOrderSysIDType		OrderSysID;		//交易所报单编号；为OrderSysID[0]为'\0'表示不限制
	uint32_t					OrderIndex;		//本地报单索引；为0xFFFFFFFF表示不限制
	int64_t						OrderRef;		//客户端第三方标识；为-1表示不限制
	uint32_t					Position;		//定位串，用于指定分页获取该记录号及之后的记录；首次输入0；后续使用应答中的Position值
	uint8_t						all_session_data;//为1表示获取所有会话的数据		

} CUftReqQueryTradeField;

//成交查询应答
typedef struct tagUftAnsQueryTradeField
{
	T_UFT_FtdcPriceType				BusinessPrice;		// 成交价格	HsFutuPrice
	int32_t							BusinessTime;		// 成交时间	HsTime
	int32_t							BusinessAmount;		// 成交数量	HsQuantity
	double							fare;				// 手续费	
	int64_t							OrderRef;			//第三方标识
	uint32_t						OrderIndex;			// 报单本地标识
	T_UFT_FtdcTradeIDType			BusinessId;		// 成交编号	HsChar32
	T_UFT_FtdcOrderSysIDType		OrderSysID;			// 报单编号，char[16], 这里未对齐
	int8_t							session_id;			//会话ID
	char							Direction;          //买卖标志
	char							OffsetFlag;         //开平标志
	char					 		InstrumentID[17];	  //合约号	
	char							StockCode[8];       //股票代码，无\0结束符

} CUftAnsQueryTradeField;

//持仓查询
typedef struct tagUftReqQueryPositionField
{
	T_UFT_FtdcInstrumentIDType	InstrumentID;	//合约代码；InstrumentID[0]为'\0'表示查所有
} CUftReqQueryPositionField;

//持仓查询应答
typedef struct tagUftAnsQueryPositionField
{
	//char		futu_code[7];		//	合约代码	HsFuturesCode;通过CFutuCode.Get获取
	//char		futu_code[9];		//	
	char		futu_code[16];		//支持铜期权，合约长度从9位扩展成16全
	char		entrust_bs;			//	买卖方向	HsType：‘0’买；‘1’卖
	T_UFT_FtdcHedgeFlagType HedgeFlag;	//投机套保标志	
//	char		reserve[7];
	char		reserve[6];
	int32_t		OldEnableAmount;	//	老仓可用数量	HsQuantity
	int32_t		OldCurrentAmount;	//	老仓持仓数量	HsQuantity
	int32_t		TodayEnableAmount;//	当日可用数量	HsQuantity
	int32_t		TodayCurrentAmount;//	当日持仓数量	HsQuantity
	T_UFT_FtdcMoneyType	OldOpenBalance;	//	老仓持仓成交额	HsAmount
	T_UFT_FtdcMoneyType	TodayOpenBalance;	//	今仓持仓成交额	HsAmount
	T_UFT_FtdcMoneyType	HoldMargin;		//	持仓保证金	HsAmount
	char		StockCode[8];		//股票代码，无\0结束符，不足以空格补齐
	int64_t		EnableAmount;		//	可用数量	HsQuantity 4
	int64_t		CurrentAmount;		//	持仓数量	HsQuantity 4
} CUftAnsQueryPositionField;





// 错误应答，280字节
typedef struct tagUftRspErrorField
{
	int32_t			ErrorNo;
	uint32_t		OrderIndex;			// 报单本地标识
	int64_t			OrderRef;			//第三方标识
	char			ErrorMsg[256];
	uint32_t		SendID;
	

} CUftRspErrorField;



//合约状态
typedef struct tagUftRtnInstrumentStatusField
{
	///结算组代码
	T_UFT_FtdcSettlementGroupIDType	SettlementGroupID;
	///合约代码
	T_UFT_FtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	T_UFT_FtdcInstrumentStatusType	Status;
	///交易阶段编号
	T_UFT_FtdcTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	T_UFT_FtdcTimeType	EnterTime;
	///进入本状态原因
	T_UFT_FtdcInstStatusEnterReasonType	EnterReason;
	///进入本状态日期

	//T_UFT_FtdcDateType	EnterDate;
    //证券NST
	uint16_t					PlatformID;
	uint16_t					PlatformState;
}CUftRtnInstrumentStatusField;



typedef struct tagUftRspTest
{
	int32_t TimeDelay;
	
}CUftRspTest;

typedef struct tagUftRspUserLoginField
{													   
	T_UFT_ORDERREF_TYPE MaxOrderRef;
	T_UFT_TRADEDATE_TYPE TradeDate;
}CUftRspUserLoginField;

typedef struct tagUftRspInfoField
{
	///错误代码
	T_UFT_ErrorIDType	ErrorID;
	///错误信息
	T_UFT_ErrorMsgType	ErrorMsg;
}CUftRspInfoField;

#endif
