
#if !defined(NH_SZSESTRUCT_H)
#define NH_SZSESTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NhStockUserApiDataType.h"

namespace nhtd
{

    ///响应信息
    struct CStockFtdcRspInfoField
    {
        ///错误代码
        TStockFtdcErrorIDType	ErrorID;
        ///错误信息
        TStockFtdcErrorMsgType	ErrorMsg;
    };


    ///期权报单请求
    struct CStockFtdcOptionsInsertReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcOwnerTypeType	OwnerType;	//订单所有类型
        TStockFtdcPriceType Price;							//申报价格，对于市价订单无意义，单位：元（精确到0.0001元）
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcSideType  Side;									//买卖方向
        TStockFtdcPositionEffectType PositionEffect;	//开仓/平仓
        TStockFtdcOrdTypeType OrdType;						//订单类型
        TStockFtdcTimeInForceType TimeInForce; 		//订单有效时间类型
        TStockFtdcCoveredOrUncoveredType CoveredOrUncovered;		//备兑标签
        TStockFtdcPartyIDType PartyID;							//投资者帐户
    };

    ///期权报单应答
    struct CStockFtdcOptionsInsertRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcExecTypeType	ExecType;			//当前订单执行类型
        TStockFtdcOrdStatusType	OrdStatus;			//当前申报的状态
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcTimeType	TransactTimeOnly;	//接受请求时间
        TStockFtdcPriceType	DiscretionPrice;		//对应申报市价转限价的订单，这里填写转为限价订单的价格，单位：元（精确到0.0001元
        TStockFtdcVolumeType	LeavesQty;				//对应申报是市价转撤单的时候，这里填写自动撤单的数量；对应申报是市价转限价的时候，这里填写转为限价订单的数量；当对应申报是限价订单时，填写撤单成功的数量；缺省填0
    };

    ///期权撤单请求
    struct CStockFtdcOptionsCancelReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcClOrdIDType 	OrigClOrdID;		//原始交易客户方订单编号
        TStockFtdcOrderIDType	OrderID;				//交易所订单编号(OrigClOrdID和OrderID任意一个即可)
    };

    ///期权撤单应答
    struct CStockFtdcOptionsCancelRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcExecTypeType	ExecType;			//当前订单执行类型
        TStockFtdcOrdStatusType	OrdStatus;			//当前申报的状态
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcClOrdIDType 	OrigClOrdID;		//原始交易客户方订单编号
        TStockFtdcTimeType	TransactTimeOnly;	//接受请求时间
        TStockFtdcPriceType	DiscretionPrice;		//对应申报市价转限价的订单，这里填写转为限价订单的价格，单位：元（精确到0.0001元
        TStockFtdcVolumeType	LeavesQty;				//对应申报是市价转撤单的时候，这里填写自动撤单的数量；对应申报是市价转限价的时候，这里填写转为限价订单的数量；当对应申报是限价订单时，填写撤单成功的数量；缺省填0
    };

    ///期权报价请求
    struct CStockFtdcQuoteInsertReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;		//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcOwnerTypeType	OwnerType;		//订单所有类型
        TStockFtdcPartyIDType PartyID;			//投资者帐户
        TStockFtdcQuoteReqIDType QuoteReqID;//报价请求ID,预留字段,当报价是对请求的响应时，填写报价请求的ID
        TStockFtdcPriceType BidPx;//买报价
        TStockFtdcPriceType AskPx;//卖报价
        TStockFtdcVolumeType BidSize;//买数量
        TStockFtdcVolumeType AskSize;//卖数量
        TStockFtdcPositionEffectType BidPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
        TStockFtdcPositionEffectType AskPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
    };

    ///期权报价应答
    struct CStockFtdcQuoteInsertRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcExecTypeType	ExecType;			//当前订单执行类型
        TStockFtdcOrdStatusType	OrdStatus;			//当前申报的状态
        TStockFtdcClOrdIDType 	ClOrdID;		//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcOwnerTypeType	OwnerType;		//订单所有类型
        TStockFtdcPartyIDType PartyID;			//投资者帐户
        TStockFtdcQuoteReqIDType QuoteReqID;//报价请求ID,预留字段,当报价是对请求的响应时，填写报价请求的ID
        TStockFtdcPriceType BidPx;//买报价
        TStockFtdcPriceType AskPx;//卖报价
        TStockFtdcVolumeType BidSize;//买数量
        TStockFtdcVolumeType AskSize;//卖数量
        TStockFtdcPositionEffectType BidPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
        TStockFtdcPositionEffectType AskPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
    };

    ///期权撤销报价请求
    struct CStockFtdcQuoteCancelReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;			//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcClOrdIDType 	OrigClOrdID;		//原始交易客户方订单编号
        TStockFtdcOrderIDType	OrderID;			//交易所订单编号(OrigClOrdID和OrderID任意一个即可)
    };

    ///期权撤销报价应答
    struct CStockFtdcQuoteCancelRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcExecTypeType	ExecType;			//当前订单执行类型
        TStockFtdcOrdStatusType	OrdStatus;			//当前申报的状态
        TStockFtdcSecurityIDType	SecurityID;			//合约编码
        TStockFtdcClOrdIDType	ClOrdID;			//会员内部订单编号
        TStockFtdcClOrdIDType 	OrigClOrdID;		//原始交易客户方订单编号
    };

    ///行权请求
    struct CStockFtdcExerciseReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcOwnerTypeType	OwnerType;	//订单所有类型
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcPartyIDType PartyID;					//投资者帐户
    };

    ///行权应答
    struct CStockFtdcExerciseRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcOwnerTypeType	OwnerType;	//订单所有类型
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcPartyIDType PartyID;					//投资者帐户
    };

    ///撤销行权请求
    struct CStockFtdcExerciseCancelReqField
    {
        TStockFtdcClOrdIDType 	OrigClOrdID;		//原始交易客户方订单编号
        TStockFtdcOrderIDType	OrderID;			//交易所订单编号(OrigClOrdID和OrderID任意一个即可)
    };
    ///撤销行权应答
    struct CStockFtdcExerciseCancelRspField
    {
        TStockFtdcClOrdIDType 	 OrigClOrdID;		//原始交易客户方订单编号
    };

    ///询价请求
    struct CStockFtdcForQuoteReqField
    {
        TStockFtdcSecurityIDType	SecurityID;			//合约编码
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcClOrdIDType	ClOrdID;			//会员内部订单编号
        TStockFtdcQuoteReqIDType QuoteReqID;//报价请求ID

    };

    ///询价应答
    struct CStockFtdcForQuoteRspField
    {
        TStockFtdcSecurityIDType	SecurityID;			//合约编码
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcPartyIDType	PartyID;				//投资者帐户
        TStockFtdcClOrdIDType	ClOrdID;			//会员内部订单编号
        TStockFtdcQuoteReqIDType QuoteReqID;//报价请求ID
    };

    ///行权通知
    struct CStockFtdcExerciseRtnField
    {
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcOwnerTypeType	OwnerType;	//订单所有类型
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcPartyIDType PartyID;					//投资者帐户
        TStockFtdcTimeType	TransactTimeOnly;	//接受请求时间
    };

    ///期权委托回报
    struct CStockFtdcOptionsOrderField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcVolumeType TradeQty;				//成交数量
        TStockFtdcVolumeType CancelQty;			//撤单数量,对应申报是市价转撤单的时候，这里填写自动撤单的数量；对应申报是市价转限价的时候，这里填写转为限价订单的数量；当对应申报是限价订单时，填写撤单成功的数量；缺省填0
        TStockFtdcPriceType Price;							//申报价格，对于市价订单无意义
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcSideType  Side;							//买卖方向
        TStockFtdcPriceType	DiscretionPrice;		//对应申报市价转限价的订单，这里填写转为限价订单的价格
        TStockFtdcPositionEffectType PositionEffect;	//开仓/平仓
        TStockFtdcCoveredOrUncoveredType CoveredOrUncovered;		//备兑标签
        TStockFtdcTimeType TransactTimeOnly;	//订单执行时间
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcOrdStatusType OrdStatus;			//当前订单状态
        TStockFtdcOrdTypeType OrdType;				//订单类型
        TStockFtdcTimeInForceType TimeInForce; 		//订单有效时间类型
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcUserIDType  UserID;				//原始报单交易用户代码
        TStockFtdcOrdRejReasonType OrdRejReason;		//报单拒绝原因代码
    };

    ///期权成交回报
    struct CStockFtdcOptionsTradeField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcExecIDType ExecID;				//成交编号
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcPriceType LastPx;						//成交价格
        TStockFtdcVolumeType LastQty;					//成交数量
        TStockFtdcVolumeType LeavesQty;			//本次成交后申报余额数量
        TStockFtdcSideType  Side;									//买卖方向
        TStockFtdcPositionEffectType PositionEffect;	//开仓/平仓
        TStockFtdcCoveredOrUncoveredType CoveredOrUncovered;		//备兑标签
        TStockFtdcTimeType TransactTimeOnly;	//订单执行时间
        TStockFtdcTimeType OrigTime;					//原有订单请求接收的时间
        TStockFtdcExecTypeType ExecType;					//订单执行状态，取值：F=成交
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcOrdStatusType OrdStatus;				//当前订单状态
        TStockFtdcPriceType TotalValueTraded;			//成交金额
        TStockFtdcPartyIDType PartyID;							//投资者帐户
    };

    ///出入金通知
    struct CStockFtdcWithdrawDepositRtnField
    {
        TStockFtdcPartyIDType AccountID;							//资金帐户
        TStockFtdcPartyIDType PartyID;							//投资者帐户
        TStockFtdcPriceType	deposit;								//入金金额
        TStockFtdcPriceType	withdraw;							//出金金额
    };

    ///股票报单请求
    struct CStockFtdcStockInsertReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;				//合约编码
        TStockFtdcOrdTypeType OrdType;					//订单类型
        TStockFtdcPriceType Price;						//申报价格，对于市价订单无意义，单位：元（精确到0.001元）
        TStockFtdcVolumeType OrderQty;					//申报数量（张）
        TStockFtdcSideType  Side;						//买卖方向
        TStockFtdcPartyIDType PartyID;					//投资者帐户
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcTimeInForceType TimeInForce; 	//订单有效时间类型
    };

    struct CStockFtdcStockInsertRspField
    {
        TStockFtdcOrderIDType OrderID;			//交易所订单编号
        TStockFtdcDateType InsertDate;				//记录写入日期
        TStockFtdcTimeType InsertTime;				//接收确认时间
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号,
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcOrdTypeType OrdType;					//订单类型
        TStockFtdcPriceType Price;						//申报价格，对于市价订单无意义
        TStockFtdcVolumeType OrderQty;			//申报数量（张）
        TStockFtdcSideType  Side;						//买卖方向
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcVolumeType Qty2;					//撤单数量，对于限价订单申报记录，该字段为空；对于撤单记录，该字段为实际撤单返回数量；对于最优五档即时成交剩余自动撤销的市价订单，如果申报部分成交，该字段取值为自动撤单的数量；如果申报全部成交，则该字段取值为0。
    };

    ///股票撤单请求
    struct CStockFtdcStockCancelReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcClOrdIDType 	OrigClOrdID;		//原始交易客户方订单编号
        TStockFtdcOrderIDType	OrderID;				//交易所订单编号
    };

    struct CStockFtdcStockCancelRspField
    {
        TStockFtdcOrderIDType OrderID;			//交易所订单编号
        TStockFtdcDateType InsertDate;				//记录写入日期
        TStockFtdcTimeType InsertTime;				//接收确认时间
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcPriceType Price;						//申报价格，对于市价订单无意义
        TStockFtdcVolumeType OrderQty;			//申报数量（张）
        TStockFtdcSideType  Side;						//买卖方向
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcClOrdIDType OrigClOrdId;	//原始会员内部编号(撤单时使用对应交易所的ordrec)
        TStockFtdcVolumeType Qty2;					//撤单数量，对于限价订单申报记录，该字段为空；对于撤单记录，该字段为实际撤单返回数量；对于最优五档即时成交剩余自动撤销的市价订单，如果申报部分成交，该字段取值为自动撤单的数量；如果申报全部成交，则该字段取值为0。
    };

    ///证券锁定请求
    struct CStockFtdcStockLockReqField
    {
        TStockFtdcClOrdIDType 		ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType	SecurityID;			//合约编码
        TStockFtdcVolumeType			OrderQty;			//申报数量（张）
        TStockFtdcLockType				Locked;				//锁定标志
        TStockFtdcPartyIDType			PartyID;				//投资者帐户
    };

    struct CStockFtdcStockLockRspField
    {
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcVolumeType OrderQty;			//申报数量（张）
        TStockFtdcPartyIDType PartyID;				//投资者帐户
    };

    ///股票委托
    struct CStockFtdcStockOrderField
    {
        TStockFtdcOrderIDType OrderID;			//交易所订单编号
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcPriceType Price;						//申报价格，对于市价订单无意义
        TStockFtdcVolumeType OrderQty;			//申报数量（张）
        TStockFtdcSideType  Side;						//买卖方向
        TStockFtdcOrdStatusType OrdStatus;	//当前订单状态
        TStockFtdcVolumeType Qty2;					//撤单数量，对于限价订单申报记录，该字段为空；对于撤单记录，该字段为实际撤单返回数量；对于最优五档即时成交剩余自动撤销的市价订单，如果申报部分成交，该字段取值为自动撤单的数量；如果申报全部成交，则该字段取值为0。
        TStockFtdcVolumeType TradeQty;			//成交数量
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcUserIDType  UserID;				//原始报单交易用户代码
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcTimeInForceType TimeInForce; 	//订单有效时间类型
        TStockFtdcOrdRejReasonType OrdRejReason;		//报单拒绝原因代码
    };

    ///股票成交回报
    struct CStockFtdcStockTradeField
    {
        TStockFtdcOrderIDType OrderID;			//交易所订单编号
        TStockFtdcTradeIDType TradeID;				//成交编号
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcDateType InsertDate;				//记录写入日期
        TStockFtdcTimeType InsertTime;				//申报时间，格式为HHMMSS
        TStockFtdcTimeType TradeTime;			//成交时间，格式为HHMMSS
        TStockFtdcTradeVolumeType	TradeVolume;	//成交数量
        TStockFtdcSideType  Side;						//买卖方向
        TStockFtdcPriceType Cjjg;							//成交价格
        TStockFtdcPriceType Cjje;							//成交金额
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号
    };

    ///报价回报
    struct CStockFtdcQuoteOrderField
    {
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcOrdStatusType OrdStatus;	//当前订单状态
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcUserIDType  UserID;				//原始报单交易用户代码
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcQuoteReqIDType QuoteReqID;//报价请求ID,预留字段,当报价是对请求的响应时，填写报价请求的ID
        TStockFtdcPriceType BidPx;//买报价
        TStockFtdcPriceType AskPx;//卖报价
        TStockFtdcVolumeType BidSize;//买数量
        TStockFtdcVolumeType AskSize;//卖数量
        TStockFtdcPositionEffectType BidPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
        TStockFtdcPositionEffectType AskPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
        TStockFtdcOrdRejReasonType OrdRejReason;		//报价拒绝原因代码
    };

    ///信息分发
    struct CStockFtdcDisseminationField
    {
        ///序列系列号
        TStockFtdcSequenceNoType	SequenceSeries;
        ///序列号
        TStockFtdcSequenceNoType	SequenceNo;
    };


    ///用户登录请求
    struct CStockFtdcReqUserLoginField
    {
        ///交易日
        TStockFtdcDateType	TradingDay;
        ///交易用户代码
        TStockFtdcUserIDType	UserID;
        ///密码
        TStockFtdcPasswordType	Password;
        ///用户端产品信息
        TStockFtdcProductInfoType	UserProductInfo;
        ///接口端产品信息
        TStockFtdcProductInfoType	InterfaceProductInfo;
        ///协议信息
        TStockFtdcProtocolInfoType	ProtocolInfo;
        ///数据中心代码
        TStockFtdcDataCenterIDType	DataCenterID;
    };

    ///用户登录应答
    struct CStockFtdcRspUserLoginField
    {
        ///交易日
        TStockFtdcDateType	TradingDay;
        ///登录成功时间
        TStockFtdcTimeType	LoginTime;
        ///最大会员内部订单编号
        TStockFtdcClOrdIDType	MaxClOrdID;
        ///交易用户代码
        TStockFtdcUserIDType	UserID;
        ///交易系统名称
        TStockFtdcTradingSystemNameType	TradingSystemName;
        ///数据中心代码
        TStockFtdcDataCenterIDType	DataCenterID;
        ///会员私有流当前长度
        TStockFtdcSequenceNoType	PrivateFlowSize;
        ///交易员私有流当前长度
        TStockFtdcSequenceNoType	UserFlowSize;
        ///业务发生日期
        TStockFtdcDateType	ActionDay;
    };

    ///用户登出请求
    struct CStockFtdcReqUserLogoutField
    {
        ///交易用户代码
        TStockFtdcUserIDType	UserID;
    };

    ///用户登出应答
    struct CStockFtdcRspUserLogoutField
    {
        ///交易用户代码
        TStockFtdcUserIDType	UserID;
    };

    ///用户口令修改
    struct CStockFtdcUserPasswordUpdateField
    {
        ///交易用户代码
        TStockFtdcUserIDType	UserID;
        ///旧密码
        TStockFtdcPasswordType	OldPassword;
        ///新密码
        TStockFtdcPasswordType	NewPassword;
    };

    ///股票报单查询
    struct CStockFtdcQryStockOrderField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///会员内部订单编号
        TStockFtdcClOrdIDType 	ClOrdID;
        ///合约编码
        TStockFtdcSecurityIDType	SecurityID;
    };
    struct CStockFtdcRspQryStockOrderField
    {
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcDateType InsertDate;				//记录写入日期
        TStockFtdcTimeType InsertTime;				//接收确认时间
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号,
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcOrdTypeType OrdType;					//订单类型
        TStockFtdcPriceType Price;						//申报价格，对于市价订单无意义
        TStockFtdcVolumeType OrderQty;			//申报数量（张）
        TStockFtdcSideType  Side;						//买卖方向
        TStockFtdcVolumeType Qty2;					//撤单数量，对于限价订单申报记录，该字段为空；对于撤单记录，该字段为实际撤单返回数量；对于最优五档即时成交剩余自动撤销的市价订单，如果申报部分成交，该字段取值为自动撤单的数量；如果申报全部成交，则该字段取值为0。
        TStockFtdcOrdStatusType OrdStatus;	//当前订单状态
    };

    ///期权报单查询
    struct CStockFtdcQryOptionsOrderField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///会员内部订单编号
        TStockFtdcClOrdIDType 	ClOrdID;
        ///合约编码
        TStockFtdcSecurityIDType	SecurityID;
    };
    struct CStockFtdcRspQryOptionsOrderField
    {
        TStockFtdcPartyIDType PartyID;					//投资者帐户
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcExecTypeType	ExecType;			//当前订单执行类型
        TStockFtdcOrdStatusType	OrdStatus;			//当前申报的状态
        TStockFtdcSecurityIDType	SecurityID;		//合约编码
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcTimeType	TransactTimeOnly;	//接受请求时间
        TStockFtdcPriceType	DiscretionPrice;		//对应申报市价转限价的订单，这里填写转为限价订单的价格，单位：元（精确到0.0001元
        TStockFtdcVolumeType	LeavesQty;				//对应申报是市价转撤单的时候，这里填写自动撤单的数量；对应申报是市价转限价的时候，这里填写转为限价订单的数量；当对应申报是限价订单时，填写撤单成功的数量；缺省填0
        TStockFtdcOwnerTypeType	OwnerType;	//订单所有类型
        TStockFtdcPriceType Price;							//申报价格，对于市价订单无意义，单位：元（精确到0.0001元）
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcSideType  Side;									//买卖方向
        TStockFtdcPositionEffectType PositionEffect;	//开仓/平仓
        TStockFtdcOrdTypeType OrdType;						//订单类型
        TStockFtdcTimeInForceType TimeInForce; 		//订单有效时间类型
        TStockFtdcCoveredOrUncoveredType CoveredOrUncovered;		//备兑标签
        TStockFtdcUserIDType UserID;		//报单对应的登录用户
    };

    ///报价查询
    struct CStockFtdcQryQuoteOrderField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///会员内部订单编号
        TStockFtdcClOrdIDType 	ClOrdID;
        ///合约编码
        TStockFtdcSecurityIDType	SecurityID;
    };
    struct CStockFtdcRspQryQuoteOrderField
    {
        TStockFtdcClOrdIDType ClOrdID;			//会员内部订单编号
        TStockFtdcSecurityIDType	SecurityID;	//合约编码
        TStockFtdcOrdStatusType OrdStatus;	//当前订单状态
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcUserIDType  UserID;				//原始报单交易用户代码
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcQuoteReqIDType QuoteReqID;//报价请求ID,预留字段,当报价是对请求的响应时，填写报价请求的ID
        TStockFtdcPriceType BidPx;//买报价
        TStockFtdcPriceType AskPx;//卖报价
        TStockFtdcVolumeType BidSize;//买数量
        TStockFtdcVolumeType AskSize;//卖数量
        TStockFtdcPositionEffectType BidPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
        TStockFtdcPositionEffectType AskPositionEffect;//平仓标识（‘ O’：开仓 ’ ‘C’：平仓 ’）
    };

    ///股票成交查询
    struct CStockFtdcQryStockTradeField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///合约编码
        TStockFtdcSecurityIDType	SecurityID;
        ///成交编号
        TStockFtdcTradeIDType TradeID;
    };

    ///期权成交查询
    struct CStockFtdcQryOptionsTradeField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///合约编码
        TStockFtdcSecurityIDType SecurityID;
        ///成交编号
        TStockFtdcExecIDType ExecID;
    };

    ///持仓查询
    struct CStockFtdcQryPositionField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///合约编码
        TStockFtdcSecurityIDType SecurityID;
    };

    ///持仓查询应答
    struct CStockFtdcRspPositionField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
        ///备兑标记
        TStockFtdcCoveredOrUncoveredType	Converd;
        ///买卖方向
        TStockFtdcSideType	Side;
        ///上日持仓
        TStockFtdcVolumeType	YdPosition;
        ///总持仓
        TStockFtdcVolumeType	Position;
        ///今日持仓
        TStockFtdcVolumeType	TodayPosition;
        ///当日买成交量
        TStockFtdcVolumeType	BuyTradeVolume;
        ///当日卖成交量
        TStockFtdcVolumeType	SellTradeVolume;
        ///持仓成本
        TStockFtdcMoneyType	PositionCost;
        ///昨日持仓成本
        TStockFtdcMoneyType	YdPositionCost;
        ///占用的保证金(权利金)
        TStockFtdcMoneyType	UseMargin;
    };

    ///资金查询
    struct CStockFtdcQryPartAccountField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
    };

    ///资金查询应答
    struct CStockFtdcRspPartAccountField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///交易日
        TStockFtdcDateType	TradingDay;
        ///上次结算准备金
        TStockFtdcMoneyType	PreBalance;
        ///期货结算准备金
        TStockFtdcMoneyType	Balance;
        ///可提资金
        TStockFtdcMoneyType	Available;
        ///当前保证金总额
        TStockFtdcMoneyType	CurrMargin;
        ///冻结的保证金
        TStockFtdcMoneyType	FrozenMargin;
        ///通过组合保证金优惠的总额
        TStockFtdcMoneyType	CombMargin;
        ///期权权利金收支
        TStockFtdcMoneyType	Premium;
        ///冻结的权利金
        TStockFtdcMoneyType	FrozenPremium;
        ///手续费
        TStockFtdcMoneyType	Commi;
        ///冻结的手续费
        TStockFtdcMoneyType	FrozenCommi;
        ///平仓盈亏
        TStockFtdcMoneyType	CloseProfit;
        ///持仓盈亏
        TStockFtdcMoneyType	PosiProfit;
        ///入金金额
        TStockFtdcMoneyType	Deposit;
        ///出金金额
        TStockFtdcMoneyType	Withdraw;
        ///基本准备金
        TStockFtdcMoneyType	BaseReserve;
        ///备用字段
        TStockFtdcMoneyType	SaveDouble1;
        ///备用字段
        TStockFtdcMoneyType	SaveDouble2;
        ///备用字段
        TStockFtdcMoneyType	SaveDouble3;
    };

    ///股票查询请求
    struct CStockFtdcQryStockField
    {
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
    };

    ///股票查询应答
    struct CStockFtdcRspQryStockField
    {
        TStockFtdcSecurityIDType	SecurityID;					//合约代码
        char contractid[20];//合约交易代码
        char contractsymbol[21];//期权合约简称
        TStockFtdcVolumeType contractmultiplierunit;//合约单位
        TStockFtdcDateType startdate;//首个交易日
        TStockFtdcDateType enddate;//最后交易日
        int updateversion;//合约版本号
        TStockFtdcVolumeType totallongposition;//当前合约未平仓数
        TStockFtdcPriceType securityclosepx;//合约前收盘价
        TStockFtdcPriceType settlprice;//合约前结算价
        TStockFtdcPriceType underlyingclosepx;//标的证券前收盘
        char pricelimittype;//涨跌幅限制类型‘N’有涨跌幅限制类型
        TStockFtdcPriceType dailypriceuplimit;//涨幅上限价格
        TStockFtdcPriceType dailypricedownlimit;//跌幅下限价格
        TStockFtdcMoneyType marginunit;//单位保证金
        TStockFtdcMoneyType marginratioparam1;//保证金计算比例参数一
        TStockFtdcMoneyType marginratioparam2;//保证金计算比例参数二
        TStockFtdcVolumeType roundlot;//整手数
        TStockFtdcVolumeType lmtordminfloor;//单笔限价申报下限
        TStockFtdcVolumeType lmtordmaxfloor;//单笔限价申报上限
        TStockFtdcVolumeType mktordminfloor;//单笔市价申报下限
        TStockFtdcVolumeType mktordmaxfloor;//单笔市价申报上限
        TStockFtdcPriceType ticksize;//最小报价单位
        TStockFtdcPriceType lastprice;//合约最新价格，行情实时更新
    };

    ///期权查询请求
    struct CStockFtdcQryOptionsField
    {
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
    };

    ///期权查询应答
    struct CStockFtdcRspQryOptionsField
    {
        TStockFtdcSecurityIDType	SecurityID;					//合约代码
        char contractid[20];//合约交易代码
        char contractsymbol[21];//期权合约简称
        TStockFtdcSecurityIDType underlyingsecurityid;//标的证券代码
        char underlyingsymbol[9];//基础证券证券名称
        char underlyingtype[4];//标的证券类型(EBS – ETF， ASH – A股)
        TStockFtdcOptionTypeType optiontype;//期权类型
        TStockFtdcCallOrPutType callorput;//认购认沽
        TStockFtdcVolumeType contractmultiplierunit;//合约单位
        TStockFtdcPriceType exerciseprice;//期权行权价
        TStockFtdcDateType startdate;//首个交易日
        TStockFtdcDateType enddate;//最后交易日
        TStockFtdcDateType exercisedate;//期权行权日
        TStockFtdcDateType deliverydate;//行权交割日
        TStockFtdcDateType expiredate;//期权到期日
        int updateversion;//合约版本号
        TStockFtdcVolumeType totallongposition;//当前合约未平仓数
        TStockFtdcPriceType securityclosepx;//合约前收盘价
        TStockFtdcPriceType settlprice;//合约前结算价
        TStockFtdcPriceType underlyingclosepx;//标的证券前收盘
        char pricelimittype;//涨跌幅限制类型‘N’有涨跌幅限制类型
        TStockFtdcPriceType dailypriceuplimit;//涨幅上限价格
        TStockFtdcPriceType dailypricedownlimit;//跌幅下限价格
        TStockFtdcMoneyType marginunit;//单位保证金
        TStockFtdcMoneyType marginratioparam1;//保证金计算比例参数一
        TStockFtdcMoneyType marginratioparam2;//保证金计算比例参数二
        TStockFtdcVolumeType roundlot;//整手数
        TStockFtdcVolumeType lmtordminfloor;//单笔限价申报下限
        TStockFtdcVolumeType lmtordmaxfloor;//单笔限价申报上限
        TStockFtdcVolumeType mktordminfloor;//单笔市价申报下限
        TStockFtdcVolumeType mktordmaxfloor;//单笔市价申报上限
        TStockFtdcPriceType ticksize;//最小报价单位
        TStockFtdcPriceType lastprice;//合约最新价格，行情实时更新
    };

    ///期权费率请求
    struct CStockFtdcQryRateField
    {
        ///投资者帐户(必填字段)
        TStockFtdcPartyIDType PartyID;
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
    };

    ///手续费信息
    typedef struct Commi_Info
    {
        TStockFtdcMoneyType	bymoney;				//按比例收取
        TStockFtdcMoneyType	byvolume;				//按手数收取
        TStockFtdcMoneyType	maxcommi;			//最高
        TStockFtdcMoneyType	mincommi;			//最低
    }Commi_Info_t;
    ///期权费率应答
    struct CStockFtdcRspQryRateField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
        TStockFtdcMoneyType Margin;			//期权保证金
        Commi_Info_t BuyOpenCommi;		//买开手续费
        Commi_Info_t SelOpenCommi;			//卖开手续费
        Commi_Info_t CovOpenCommi;		//备兑开手续费
        Commi_Info_t BuyCloseCommi;		//买平手续费
        Commi_Info_t SelCloseCommi;			//卖平手续费
        Commi_Info_t CovCloseCommi;		//备兑平手续费
    };



    ///期权保证金请求
    struct CStockFtdcQryClientMarginField
    {
        ///投资者帐户(必填字段)
        TStockFtdcPartyIDType PartyID;
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
    };
    ///期权保证金应答
    struct CStockFtdcRspQryClientMarginField
    {
        ///投资者帐户
        TStockFtdcPartyIDType PartyID;
        ///合约代码
        TStockFtdcSecurityIDType	SecurityID;
        TStockFtdcMoneyType Margin;									//期权保证金
        TStockFtdcMoneyType MarginRatio;							//标的保证金率
        TStockFtdcMoneyType MinMarginRatio;					//最低保障系数
    };

    ///客户查询应答
    struct CStockFtdcRspClientField
    {
        TStockFtdcPartyIDType PartyID;							//投资者帐户
        TStockFtdcClientTypeType	ClientType;		///投资者类型
        TStockFtdcTradStatusType Status;															//交易状态:0:正常,1:禁止交易
    };

    ///行权查询请求
    struct CStockFtdcQryExerciseField
    {
        TStockFtdcPartyIDType PartyID;							//投资者帐户
    };

    struct OmlItem
    {
        TStockFtdcSecurityIDType LegSecurityID;	//合约编码
        char LegSide;			//合约方向，L为权利仓, S为义务仓
        TStockFtdcCoveredOrUncoveredType CoveredOrUncovered;// 备兑标签
        TStockFtdcVolumeType LegOrderQty;		//申报数量
    };

    ///客户申请组合请求
    struct CStockFtdcMarginCombActionField
    {
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType CombID;			//组合策略编码:目前为7种组合策略：CNSJC、PXSJC、PNSJC、CXSJC、KS、KKS、ZBD
        TStockFtdcOwnerTypeType	OwnerType;				//订单所有类型
        TStockFtdcVolumeType OrderQty;					//申报数量（张）
        char  Side;						//买卖方向,取值：B表示组合，C表示拆分,组合策略为“ZBD”时，组合与拆分方向只能为‘B’，
        char SecondaryOrderID[17];//组合编码ID,组合申报时，该字段为空格；拆分申报时，填写拟拆分组合的组合编码
        TStockFtdcPartyIDType PartyID;							//投资者帐户
        int NoLeges;//成分合约数，取值不超过4，后接重复组
        OmlItem item[4];
    };
    ///客户申请组合应答
    struct CStockFtdcMarginCombActionRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcClOrdIDType 	ClOrdID;				//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcSecurityIDType CombID;			//组合策略编码:目前为7种组合策略：CNSJC、PXSJC、PNSJC、CXSJC、KS、KKS、ZBD
        TStockFtdcOwnerTypeType	OwnerType;				//订单所有类型
        TStockFtdcVolumeType OrderQty;					//申报数量（张）
        char  Side;						//买卖方向,取值：B表示组合，C表示拆分,组合策略为“ZBD”时，组合与拆分方向只能为‘B’，
        char SecondaryOrderID[17];//组合编码ID,组合申报时，该字段为空格；拆分申报时，填写拟拆分组合的组合编码
        TStockFtdcPartyIDType PartyID;							//投资者帐户
        int NoLeges;//成分合约数，取值不超过4，后接重复组
        OmlItem item[4];
    };
    ///客户申请组合通知
    struct CStockFtdcMarginCombActionRtnField
    {
        TStockFtdcClOrdIDType	ClOrdID;					//会员内部订单编号
        TStockFtdcExecIDType ExecID;				//成交编号
        TStockFtdcSecurityIDType CombID;			//组合策略编码:目前为7种组合策略：CNSJC、PXSJC、PNSJC、CXSJC、KS、KKS、ZBD
        TStockFtdcTimeType TransactTimeOnly;	//订单执行时间
        TStockFtdcTimeType OrigTime;					//原有订单请求接收的时间
        TStockFtdcPartyIDType PartyID;							//投资者帐户
        char  Side;						//买卖方向,取值：B表示组合，C表示拆分,组合策略为“ZBD”时，组合与拆分方向只能为‘B’，
        char SecondaryOrderID[17];//组合编码ID,组合申报时，该字段为空格；拆分申报时，填写拟拆分组合的组合编码
        TStockFtdcVolumeType LastQty;					//执行数量（张）
        int NoLeges;//成分合约数，取值不超过4，后接重复组
        OmlItem item[4];
        TStockFtdcPriceType commargin;//组合或拆分后保证金的变化值(组合为正拆分为负)
    };
    ///上期所组合持仓查询请求
    struct CStockFtdcCombPositionField
    {
        TStockFtdcPartyIDType PartyID;			//投资者帐户
        char SecondaryOrderID[17];//组合编码ID
    };
    ///上期所组合持仓查询应答
    struct CStockFtdcCombPositionRspField
    {
        TStockFtdcPartyIDType PartyID;			//投资者帐户
        char SecondaryOrderID[17];//组合编码ID
        TStockFtdcVolumeType PosiQty;					//持仓数量
        TStockFtdcPriceType commargin;	//优惠的保证金
        int NoLeges;//成分合约数，取值不超过4，后接重复组
        OmlItem item[4];
    };
    ///组合行权请求
    struct CStockFtdcCombExerciseReqField
    {
        TStockFtdcClOrdIDType 	ClOrdID;			//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcSecurityIDType LegSecurityID1;	//合约编码
        TStockFtdcVolumeType LegOrderQty1;		//申报数量
        TStockFtdcSecurityIDType LegSecurityID2;	//合约编码
        TStockFtdcVolumeType LegOrderQty2;		//申报数量
    };

    ///组合行权应答
    struct CStockFtdcCombExerciseRspField
    {
        TStockFtdcOrderIDType OrderID;				//交易所订单编号
        TStockFtdcClOrdIDType 	ClOrdID;			//会员内部订单编号,在所有申报业务范围内，同一个交易单元的会员内部编号必须唯一，交易系统不重复处理前台提交的同一个交易单元相同的会员内部编号订单，并以此编号重复作为订单重复依据。
        TStockFtdcOwnerTypeType	OwnerType;			//订单所有类型
        TStockFtdcVolumeType OrderQty;				//申报数量（张）
        TStockFtdcPartyIDType PartyID;				//投资者帐户
        TStockFtdcSecurityIDType LegSecurityID1;	//合约编码
        TStockFtdcVolumeType LegOrderQty1;		//申报数量
        TStockFtdcSecurityIDType LegSecurityID2;	//合约编码
        TStockFtdcVolumeType LegOrderQty2;		//申报数量
    };
}


#endif
