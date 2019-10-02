/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xoms_api_struct.h
///@brief 定义交易类相关数据结构
/////////////////////////////////////////////////////////////////////////
#ifndef _XOMS_API_STRUCT_H_
#define _XOMS_API_STRUCT_H_

#include "xtp_api_data_type.h"
#include "stddef.h"
#include "xtp_api_struct_common.h"

#pragma pack(8)

//=====================客户端接口定义=================================
///新订单请求
struct XTPOrderInsertInfo
{
    ///XTP系统订单ID，无需用户填写，在XTP系统中唯一
    uint64_t                order_xtp_id;
    ///报单引用，由客户自定义
    uint32_t	            order_client_id;
    ///合约代码 客户端请求不带空格，以'\0'结尾
    char                    ticker[XTP_TICKER_LEN];
    ///交易市场
    XTP_MARKET_TYPE         market;
    ///价格
    double                  price;
    ///止损价（保留字段）
    double                  stop_price;
    ///数量(股票单位为股，逆回购单位为张)
    int64_t                 quantity;
    ///报单价格
    XTP_PRICE_TYPE          price_type;
    union{
		///32位字段，用来兼容老版本api，用户无需关心
        uint32_t            u32;
        struct {
            ///买卖方向
            XTP_SIDE_TYPE               side;
            ///开平标志
            XTP_POSITION_EFFECT_TYPE    position_effect;
			///预留字段1
            uint8_t                     reserved1;
			///预留字段2
			uint8_t                     reserved2;
        };
    };
	///业务类型
	XTP_BUSINESS_TYPE       business_type;
 };


///撤单失败响应消息
struct XTPOrderCancelInfo
{
    ///撤单XTPID
    uint64_t                 order_cancel_xtp_id;
    ///原始订单XTPID
    uint64_t                 order_xtp_id;
};


///报单响应结构体
struct XTPOrderInfo
{
    ///XTP系统订单ID，在XTP系统中唯一
	uint64_t                order_xtp_id;
	///报单引用，用户自定义
	uint32_t	            order_client_id;
    ///报单操作引用，用户自定义（暂未使用）
    uint32_t                order_cancel_client_id;
    ///撤单在XTP系统中的id，在XTP系统中唯一
    uint64_t                order_cancel_xtp_id;
	///合约代码
	char                    ticker[XTP_TICKER_LEN];
	///交易市场
	XTP_MARKET_TYPE         market;
	///价格
	double                  price;
	///数量，此订单的报单数量
	int64_t                 quantity;
	///报单价格条件
	XTP_PRICE_TYPE          price_type;
    union{
		///32位字段，用来兼容老版本api，用户无需关心
        uint32_t            u32;
        struct {
            ///买卖方向
            XTP_SIDE_TYPE               side;
            ///开平标志
            XTP_POSITION_EFFECT_TYPE    position_effect;
			///预留字段1
			uint8_t                     reserved1;
			///预留字段2
			uint8_t                     reserved2;
        };
    };
	///业务类型
	XTP_BUSINESS_TYPE       business_type;
	///今成交数量，为此订单累计成交数量
	int64_t                 qty_traded;
	///剩余数量，当撤单成功时，表示撤单数量
	int64_t                 qty_left;
	///委托时间，格式为YYYYMMDDHHMMSSsss
	int64_t                 insert_time;
	///最后修改时间，格式为YYYYMMDDHHMMSSsss
	int64_t                 update_time;
	///撤销时间，格式为YYYYMMDDHHMMSSsss
	int64_t                 cancel_time;
	///成交金额，为此订单的成交总金额
	double                  trade_amount;
	///本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
	char                    order_local_id[XTP_LOCAL_ORDER_LEN];
	///报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
	XTP_ORDER_STATUS_TYPE   order_status;
	///报单提交状态，OMS内部使用，用户无需关心
	XTP_ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
	///报单类型
	TXTPOrderTypeType       order_type;
};



///报单成交结构体
struct XTPTradeReport
{
    ///XTP系统订单ID，此成交回报相关的订单ID，在XTP系统中唯一
    uint64_t                 order_xtp_id;
    ///报单引用
    uint32_t                 order_client_id;
    ///合约代码
    char                     ticker[XTP_TICKER_LEN];
    ///交易市场
    XTP_MARKET_TYPE          market;
    ///订单号，引入XTPID后，该字段实际和order_xtp_id重复。接口中暂时保留。
    uint64_t                 local_order_id;
    ///成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
    char                     exec_id[XTP_EXEC_ID_LEN];
    ///价格，此次成交的价格
    double                   price;
    ///数量，此次成交的数量，不是累计数量
    int64_t                  quantity;
    ///成交时间，格式为YYYYMMDDHHMMSSsss
    int64_t                  trade_time;
    ///成交金额，此次成交的总金额 = price*quantity
    double                   trade_amount;
    ///成交序号 --回报记录号，对于单个账户来说，每个交易所唯一,report_index+market字段可以组成唯一标识表示成交回报，对于多账户来说，不唯一
    uint64_t                 report_index;
    ///报单编号 --交易所单号，上交所为空，深交所有此字段
    char                     order_exch_id[XTP_ORDER_EXCH_LEN];
    ///成交类型  --成交回报中的执行类型
    TXTPTradeTypeType        trade_type;
    union{
		///32位字段，用来兼容老版本api，用户无需关心
        uint32_t            u32;
        struct {
            ///买卖方向
            XTP_SIDE_TYPE               side;
            ///开平标志
            XTP_POSITION_EFFECT_TYPE    position_effect;
			///预留字段1
			uint8_t                     reserved1;
			///预留字段2
			uint8_t                     reserved2;
        };
    };
	///业务类型
	XTP_BUSINESS_TYPE        business_type;
    ///交易所交易员代码 
    char                     branch_pbu[XTP_BRANCH_PBU_LEN];
};


//////////////////////////////////////////////////////////////////////////
///报单查询
//////////////////////////////////////////////////////////////////////////
///报单查询请求-条件查询
struct XTPQueryOrderReq
{
    ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      ticker[XTP_TICKER_LEN];
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time;
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;  
};

///报单查询响应结构体
typedef struct XTPOrderInfo XTPQueryOrderRsp;


//////////////////////////////////////////////////////////////////////////
///成交回报查询
//////////////////////////////////////////////////////////////////////////
///查询成交报告请求-根据执行编号查询（保留字段）
struct XTPQueryReportByExecIdReq
{
    ///XTP订单系统ID
    uint64_t  order_xtp_id;  
    ///成交执行编号
    char  exec_id[XTP_EXEC_ID_LEN];
};

///查询成交回报请求-查询条件
struct XTPQueryTraderReq
{
    ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      ticker[XTP_TICKER_LEN];
    ///开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time; 
    ///结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;  
};

///成交回报查询响应结构体
typedef struct XTPTradeReport  XTPQueryTradeRsp;



//////////////////////////////////////////////////////////////////////////
///账户资金查询响应结构体
//////////////////////////////////////////////////////////////////////////
struct XTPQueryAssetRsp
{
    ///总资产（现货账户/期权账户参考公式：总资产 = 可用资金 + 证券资产（目前为0）+ 预扣的资金），（信用账户参考公式：总资产 = 可用资金 + 融券卖出所得资金余额 + 证券资产+ 预扣的资金）
    double total_asset;
    ///可用资金
    double buying_power;
    ///证券资产（保留字段，目前为0）
    double security_asset;
    ///累计买入成交证券占用资金（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_buy_amount;
    ///累计买入成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_buy_fee;
    ///累计卖出成交证券所得资金（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_sell_amount;
    ///累计卖出成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_sell_fee;
    ///XTP系统预扣的资金（包括买卖股票时预扣的交易资金+预扣手续费）
    double withholding_amount;
    ///账户类型
    XTP_ACCOUNT_TYPE account_type;

    ///冻结的保证金（仅限期权账户）
    double frozen_margin;
    ///行权冻结资金（仅限期权账户）
    double frozen_exec_cash;
    ///行权费用（仅限期权账户）
    double frozen_exec_fee;
    ///垫付资金（仅限期权账户）
    double pay_later;
    ///预垫付资金（仅限期权账户）
    double preadva_pay;
    ///昨日余额（仅限期权账户）
    double orig_banlance;
    ///当前余额（仅限期权账户）
    double banlance;
    ///当天出入金（仅限期权账户）
    double deposit_withdraw;
    ///当日交易资金轧差（仅限期权账户）
    double trade_netting;
    ///资金资产（仅限期权账户）
    double captial_asset;

    ///强锁资金（仅限期权账户）
    double force_freeze_amount;
    ///可取资金（仅限期权账户）
    double preferred_amount;

    // 信用业务新增字段开始（数量1）
    ///融券卖出所得资金余额（仅限信用账户，只能用于买券还券）
    double repay_stock_aval_banlance;

    // 信用业务新增字段结束（数量1）

    ///(保留字段)
    uint64_t unknown[43 - 12 - 1];
};



//////////////////////////////////////////////////////////////////////////
///查询股票持仓情况
//////////////////////////////////////////////////////////////////////////
struct XTPQueryStkPositionRsp
{
    ///证券代码
    char                ticker[XTP_TICKER_LEN];
    ///证券名称
    char                ticker_name[XTP_TICKER_NAME_LEN];
    ///交易市场
    XTP_MARKET_TYPE     market;
    ///总持仓
    int64_t             total_qty;
    ///可卖持仓
    int64_t				sellable_qty;
    ///持仓成本
    double              avg_price;
    ///浮动盈亏（保留字段）
    double              unrealized_pnl;
    ///昨日持仓
    int64_t             yesterday_position;
    ///今日申购赎回数量（申购和赎回数量不可能同时存在，因此可以共用一个字段）
    int64_t				purchase_redeemable_qty;

    /// 持仓方向
	XTP_POSITION_DIRECTION_TYPE      position_direction;
	///保留字段1
	uint32_t			reserved1;
    /// 可行权合约
    int64_t             executable_option;
    /// 可锁定标的
    int64_t             lockable_position;
    /// 可行权标的
    int64_t             executable_underlying;
    /// 已锁定标的
    int64_t             locked_position;
    /// 可用已锁定标的
    int64_t             usable_locked_position;


    ///(保留字段)
    uint64_t unknown[50 - 6];
};


/////////////////////////////////////////////////////////////////////////
///资金内转流水通知
/////////////////////////////////////////////////////////////////////////
struct XTPFundTransferNotice
{
    ///资金内转编号
    uint64_t	            serial_id;
    ///内转类型
    XTP_FUND_TRANSFER_TYPE	transfer_type;
    ///金额
    double	                amount;
    ///操作结果 
    XTP_FUND_OPER_STATUS    oper_status;
    ///操作时间
    uint64_t	            transfer_time;
};



/////////////////////////////////////////////////////////////////////////
///资金内转流水查询请求与响应
/////////////////////////////////////////////////////////////////////////
struct XTPQueryFundTransferLogReq {
    ///资金内转编号
    uint64_t	serial_id;

};

/////////////////////////////////////////////////////////////////////////
///资金内转流水记录结构体
/////////////////////////////////////////////////////////////////////////
typedef struct XTPFundTransferNotice XTPFundTransferLog;

//////////////////////////////////////////////////////////////////////////
///查询分级基金信息结构体
//////////////////////////////////////////////////////////////////////////
struct XTPQueryStructuredFundInfoReq
{
	XTP_EXCHANGE_TYPE   exchange_id;  ///<交易所代码，不可为空
	char                sf_ticker[XTP_TICKER_LEN];   ///<分级基金母基金代码，可以为空，如果为空，则默认查询所有的分级基金
};

//////////////////////////////////////////////////////////////////////////
///查询分级基金信息响应结构体
//////////////////////////////////////////////////////////////////////////
struct XTPStructuredFundInfo
{
    XTP_EXCHANGE_TYPE   exchange_id;  ///<交易所代码
	char                sf_ticker[XTP_TICKER_LEN];   ///<分级基金母基金代码
	char                sf_ticker_name[XTP_TICKER_NAME_LEN]; ///<分级基金母基金名称
    char                ticker[XTP_TICKER_LEN];   ///<分级基金子基金代码
    char                ticker_name[XTP_TICKER_NAME_LEN]; ///<分级基金子基金名称
	XTP_SPLIT_MERGE_STATUS	split_merge_status;   ///<基金允许拆分合并状态
    uint32_t            ratio; ///<拆分合并比例
    uint32_t            min_split_qty;///<最小拆分数量
    uint32_t            min_merge_qty; ///<最小合并数量
    double              net_price;///<基金净值
};


//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约基本情况--请求结构体,
///请求参数为多条件参数:1,不填则返回所有市场的ETF合约信息。
///                  2,只填写market,返回该交易市场下结果
///                   3,填写market及ticker参数,只返回该etf信息。
//////////////////////////////////////////////////////////////////////////
struct XTPQueryETFBaseReq
{
    ///交易市场
    XTP_MARKET_TYPE    market;
    ///ETF买卖代码
    char               ticker[XTP_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约基本情况--响应结构体
//////////////////////////////////////////////////////////////////////////
typedef struct XTPQueryETFBaseRsp
{
    XTP_MARKET_TYPE     market;                             ///<交易市场
    char                etf[XTP_TICKER_LEN];                ///<etf代码,买卖,申赎统一使用该代码
    char                subscribe_redemption_ticker[XTP_TICKER_LEN];    ///<etf申购赎回代码
    int32_t             unit;                               ///<最小申购赎回单位对应的ETF份数,例如上证"50ETF"就是900000
    int32_t             subscribe_status;                   ///<是否允许申购,1-允许,0-禁止
    int32_t             redemption_status;                  ///<是否允许赎回,1-允许,0-禁止
    double              max_cash_ratio;                     ///<最大现金替代比例,小于1的数值   TODO 是否采用double
    double              estimate_amount;                    ///<T日预估金额
    double              cash_component;                     ///<T-X日现金差额
    double              net_value;                          ///<基金单位净值
    double              total_amount;                       ///<最小申赎单位净值总金额=net_value*unit
}XTPQueryETFBaseRsp;



//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约成分股信息--请求结构体,请求参数为:交易市场+ETF买卖代码
//////////////////////////////////////////////////////////////////////////
typedef struct XTPQueryETFComponentReq
{
    ///交易市场
    XTP_MARKET_TYPE     market;
    ///ETF买卖代码
    char                ticker[XTP_TICKER_LEN];
}XTPQueryETFComponentReq;


//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约成分股信息--响应结构体
//////////////////////////////////////////////////////////////////////////
struct XTPQueryETFComponentRsp
{
    ///交易市场
    XTP_MARKET_TYPE     market;
    ///ETF代码
    char                ticker[XTP_TICKER_LEN];
    ///成份股代码
    char                component_ticker[XTP_TICKER_LEN];
    ///成份股名称
    char                component_name[XTP_TICKER_NAME_LEN];
    ///成份股数量
    int64_t             quantity;
    ///成份股交易市场
    XTP_MARKET_TYPE     component_market;
    ///成份股替代标识
    ETF_REPLACE_TYPE    replace_type;
    ///溢价比例
    double              premium_ratio;
    ///成分股替代标识为必须现金替代时候的总金额
    double              amount;

};

//////////////////////////////////////////////////////////////////////////
///查询当日可申购新股信息
//////////////////////////////////////////////////////////////////////////
struct XTPQueryIPOTickerRsp {
    ///交易市场
    XTP_MARKET_TYPE     market;
    ///申购代码
    char                ticker[XTP_TICKER_LEN];
    ///申购股票名称
    char                ticker_name[XTP_TICKER_NAME_LEN]; 
    ///申购价格
    double              price;
    ///申购单元         
    int32_t             unit;
    ///最大允许申购数量
    int32_t             qty_upper_limit;
};


//////////////////////////////////////////////////////////////////////////
///查询用户申购额度
//////////////////////////////////////////////////////////////////////////
struct XTPQueryIPOQuotaRsp {
    ///交易市场
    XTP_MARKET_TYPE     market;
    ///可申购额度
    int32_t             quantity;
};

//////////////////////////////////////////////////////////////////////////
///查询期权竞价交易业务参考信息--请求结构体,请求参数为:交易市场+8位期权代码
//////////////////////////////////////////////////////////////////////////
struct XTPQueryOptionAuctionInfoReq {
    ///交易市场
    XTP_MARKET_TYPE     market;
    ///8位期权合约代码
    char                ticker[XTP_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查询期权竞价交易业务参考信息
//////////////////////////////////////////////////////////////////////////
struct XTPQueryOptionAuctionInfoRsp {
    char                ticker[XTP_TICKER_LEN];             ///<合约编码，报单ticker采用本字段
    XTP_MARKET_TYPE     security_id_source;                 ///<证券代码源
    char                symbol[XTP_TICKER_NAME_LEN];        ///<合约简称
    char                contract_id[XTP_TICKER_NAME_LEN];   ///<合约交易代码
    char                underlying_security_id[XTP_TICKER_LEN]; ///<基础证券代码
	XTP_MARKET_TYPE     underlying_security_id_source;      ///<基础证券代码源

    uint32_t            list_date;                          ///<上市日期，格式为YYYYMMDD
    uint32_t            last_trade_date;                    ///<最后交易日，格式为YYYYMMDD
    XTP_TICKER_TYPE     ticker_type;                        ///<证券类别
    int32_t             day_trading;                        ///<是否支持当日回转交易，1-允许，0-不允许

    XTP_OPT_CALL_OR_PUT_TYPE    call_or_put;                ///<认购或认沽
    uint32_t            delivery_day;                       ///<行权交割日，格式为YYYYMMDD
    uint32_t            delivery_month;                     ///<交割月份，格式为YYYYMM

    XTP_OPT_EXERCISE_TYPE_TYPE  exercise_type;              ///<行权方式
    uint32_t            exercise_begin_date;                ///<行权起始日期，格式为YYYYMMDD
    uint32_t            exercise_end_date;                  ///<行权结束日期，格式为YYYYMMDD
    double              exercise_price;                     ///<行权价格

    int64_t             qty_unit;                           ///<数量单位，对于某一证券申报的委托，其委托数量字段必须为该证券数量单位的整数倍
    int64_t             contract_unit;                      ///<合约单位
    int64_t             contract_position;                  ///<合约持仓量

    double              prev_close_price;                   ///<合约前收盘价
    double              prev_clearing_price;                ///<合约前结算价

    int64_t             lmt_buy_max_qty;                    ///<限价买最大量
    int64_t             lmt_buy_min_qty;                    ///<限价买最小量
    int64_t             lmt_sell_max_qty;                   ///<限价卖最大量
    int64_t             lmt_sell_min_qty;                   ///<限价卖最小量
    int64_t             mkt_buy_max_qty;                    ///<市价买最大量
    int64_t             mkt_buy_min_qty;                    ///<市价买最小量
    int64_t             mkt_sell_max_qty;                   ///<市价卖最大量
    int64_t             mkt_sell_min_qty;                   ///<市价卖最小量

    double              price_tick;                         ///<最小报价单位
    double              upper_limit_price;                  ///<涨停价
    double              lower_limit_price;                  ///<跌停价
    double              sell_margin;                        ///<今卖开每张保证金
    double              margin_ratio_param1;                ///<交易所保证金比例计算参数一
    double              margin_ratio_param2;                ///<交易所保证金比例计算参数二

    uint64_t            unknown[20];                        ///<（保留字段）
};


//////////////////////////////////////////////////////////////////////////
///融资融券直接还款响应信息
//////////////////////////////////////////////////////////////////////////
struct XTPCrdCashRepayRsp
{
    int64_t xtp_id;             ///< 直接还款操作的XTPID
    double  request_amount;     ///< 直接还款的申请金额
    double  cash_repay_amount;  ///< 实际还款使用金额
};

//////////////////////////////////////////////////////////////////////////
///融资融券现金还息费响应信息
//////////////////////////////////////////////////////////////////////////
struct XTPCrdCashRepayDebtInterestFeeRsp
{
	int64_t xtp_id;             ///< 直接还款操作的XTPID
	double  request_amount;     ///< 直接还款的申请金额
	double  cash_repay_amount;  ///< 实际还款使用金额
	char	debt_compact_id[XTP_CREDIT_DEBT_ID_LEN]; ///< 指定的负债合约编号
	char	unknow[32];			///< 保留字段
};

//////////////////////////////////////////////////////////////////////////
///单条融资融券直接还款记录信息
//////////////////////////////////////////////////////////////////////////
struct XTPCrdCashRepayInfo
{
    int64_t                     xtp_id;             ///< 直接还款操作的XTPID
    XTP_CRD_CR_STATUS           status;             ///< 直接还款处理状态
    double                      request_amount;     ///< 直接还款的申请金额
    double                      cash_repay_amount;  ///< 实际还款使用金额
    XTP_POSITION_EFFECT_TYPE    position_effect;    ///< 强平标志
	XTPRI						error_info;			///< 直接还款发生错误时的错误信息
};

//////////////////////////////////////////////////////////////////////////
///单条融资融券负债记录信息
//////////////////////////////////////////////////////////////////////////
typedef struct XTPCrdDebtInfo
{
    int32_t             debt_type;              ///< 负债合约类型
    char                debt_id[33];            ///< 负债合约编号
    int64_t             position_id;            ///< 负债对应两融头寸编号
    uint64_t            order_xtp_id;           ///< 生成负债的订单编号，非当日负债无此项
    int32_t             debt_status;            ///< 负债合约状态
    XTP_MARKET_TYPE     market;                 ///< 市场
    char                ticker[XTP_TICKER_LEN]; ///< 证券代码
    uint64_t            order_date;             ///< 委托日期
    uint64_t            end_date;               ///< 负债截止日期
    uint64_t            orig_end_date;          ///< 负债原始截止日期
    bool                is_extended;            ///< 当日是否接收到展期请求
    double              remain_amt;             ///< 未偿还金额
    int64_t             remain_qty;             ///< 未偿还融券数量
    double              remain_principal;       ///< 未偿还本金金额
	int64_t				due_right_qty;			///< 应偿还权益数量
	int64_t				unknown[2];				///< 保留字段
}XTPCrdDebtInfo;

//////////////////////////////////////////////////////////////////////////
///融资融券特有帐户数据
//////////////////////////////////////////////////////////////////////////
typedef struct XTPCrdFundInfo
{
    double maintenance_ratio;       ///< 维持担保品比例
    double all_asset;               ///< 总资产
    double all_debt;                ///< 总负债
    double line_of_credit;          ///< 两融授信额度
    double guaranty;                ///< 两融保证金可用数
    double position_amount;         ///< 融资头寸可用金额，内部接口，正式版本需要删除
}XTPCrdFundInfo;

//////////////////////////////////////////////////////////////////////////
///融资融券指定证券上的负债未还数量请求结构体
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdDebtStockReq
{
    XTP_MARKET_TYPE market;                 ///< 市场
    char            ticker[XTP_TICKER_LEN]; ///< 证券代码
}XTPClientQueryCrdDebtStockReq;

//////////////////////////////////////////////////////////////////////////
///融资融券指定证券上的负债未还信息
//////////////////////////////////////////////////////////////////////////
typedef struct XTPCrdDebtStockInfo
{
    XTP_MARKET_TYPE market;                     ///< 市场
    char            ticker[XTP_TICKER_LEN];     ///< 证券代码
    int64_t         remain_quantity;            ///< 负债未还数量
    int64_t         order_withhold_quantity;    ///< 挂单未成还券数量
}XTPCrdDebtStockInfo;

//////////////////////////////////////////////////////////////////////////
///融券头寸证券查询请求结构体
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdPositionStockReq
{
    XTP_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[XTP_TICKER_LEN]; ///< 证券代码
}XTPClientQueryCrdPositionStockReq;

//////////////////////////////////////////////////////////////////////////
///融券头寸证券信息
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdPositionStkInfo 
{
    XTP_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[XTP_TICKER_LEN]; ///< 证券代码
    int64_t         limit_qty;              ///< 融券限量
    int64_t         yesterday_qty;          ///< 昨日日融券数量
    int64_t         left_qty;               ///< 剩余可融券数量
    int64_t         frozen_qty;             ///< 冻结融券数量
}XTPClientQueryCrdPositionStkInfo;


//////////////////////////////////////////////////////////////////////////
/// 信用业务余券查询请求结构体
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdSurplusStkReqInfo
{
    XTP_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[XTP_TICKER_LEN]; ///< 证券代码
}XTPClientQueryCrdSurplusStkReqInfo;

//////////////////////////////////////////////////////////////////////////
///信用业务余券信息
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdSurplusStkRspInfo
{
    XTP_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[XTP_TICKER_LEN]; ///< 证券代码
    int64_t         transferable_quantity;  ///< 可划转数量
    int64_t         transferred_quantity;   ///< 已划转数量
}XTPClientQueryCrdSurplusStkRspInfo;


//////////////////////////////////////////////////////////////////////////
/// 信用业务负债展期信息
//////////////////////////////////////////////////////////////////////////

typedef struct XTPClientCrdExtendDebtInfo
{
    uint64_t    xtp_id;                             ///< 订单编号
    char        debt_id[XTP_CREDIT_DEBT_ID_LEN];    ///< 待展期负债合约编号
}XTPClientCrdExtendDebtInfo;

#pragma pack()
#endif //_XOMS_API_STRUCT_H_

