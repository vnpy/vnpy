/*!
 * \file xoms_api_struct.h
 * \date 2015/10/23 16:45
 *
 * \author howellxu
 * Contact: user@company.com
 *
 * \brief 定义订单管理系统外部交互接口数据结构
 *
 * TODO: long description
 *
 * \note
*/
#ifndef _XOMS_API_STRUCT_H_
#define _XOMS_API_STRUCT_H_

#include "xtp_api_data_type.h"

#define XTP_API_TICKER_LEN  13
#define XTP_API_TICKER_NAME_LEN  48
#define XTP_LOCAL_ORDER_LEN     11
#define XTP_ORDER_EXCH_LEN      17
#define XTP_ORDER_RES_LEN       4
#define XTP_SUBPBUID_LEN        7
#define XTP_BRANCH_PBU_LEN      7
#define XTP_SYS_INSTRUMENT_LEN  24


//=====================客户端接口定义=================================
///新订单请求
struct XTPOrderInsertInfo
{
    ///XTP系统订单ID
    uint64_t                order_xtp_id;
    ///报单引用,由客户自定义
    uint32_t	            order_client_id;
    ///合约代码 客户端请求不带空格
    char                    ticker[XTP_API_TICKER_LEN];
    ///交易市场
    XTP_MARKET_TYPE         market;
    ///价格
    double                  price;
    ///止损价（保留字段）
    double                  stop_price;
    ///数量
    int64_t                 quantity;
    ///报单价格
    XTP_PRICE_TYPE          price_type;
    ///买卖方向
    XTP_SIDE_TYPE           side;  
 };

///撤单
struct XTPOrderCancel
{
    ///XTP系统订单ID
    uint64_t                 order_cancel_xtp_id;
    ///报单操作引用
    uint32_t                 order_cancel_client_id; 
    ///合约代码
    char                     ticker[XTP_API_TICKER_LEN];
    ///交易市场
    XTP_MARKET_TYPE          market;
    ///操作时间
    int64_t                  action_time;
    ///报单引用
    uint32_t                 order_client_id;
    ///操作对象订单的序号
    uint64_t                 order_xtp_id;
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
    ///XTP系统订单ID
	uint64_t                order_xtp_id;
	///报单引用，用户自定义
	uint32_t	            order_client_id;
    ///报单操作引用，用户自定义
    uint32_t                order_cancel_client_id;
    ///撤单在XTP系统中的id
    uint64_t                order_cancel_xtp_id;
	///合约代码
	char                    ticker[XTP_API_TICKER_LEN];
	///交易市场
	XTP_MARKET_TYPE         market;
	///价格
	double                  price;
	///数量
	int64_t                 quantity;
	///报单价格条件
	XTP_PRICE_TYPE          price_type;
	///买卖方向
	XTP_SIDE_TYPE           side;
	///今成交数量
	int64_t                 qty_traded;
	///剩余数量
	int64_t                 qty_left;
	///委托时间
	int64_t                 insert_time;
	///最后修改时间
	int64_t                 update_time;
	///撤销时间
	int64_t                 cancel_time;
	///成交金额
	double                  trade_amount;
	///本地报单编号 OMS生成的单号
	char                    order_local_id[XTP_LOCAL_ORDER_LEN];
	///报单状态
	XTP_ORDER_STATUS_TYPE   order_status;
	///报单提交状态
	XTP_ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
	///报单类型
	TXTPOrderTypeType       order_type;
};



///报单成交结构体
struct XTPTradeReport
{
    ///XTP系统订单ID
    uint64_t                 order_xtp_id;
    ///报单引用
    uint32_t                 order_client_id;
    ///合约代码
    char                     ticker[XTP_API_TICKER_LEN];
    ///交易市场
    XTP_MARKET_TYPE          market;
    ///订单号
    uint64_t                 local_order_id;
    ///成交编号
    uint64_t                 exec_id;
    ///价格
    double                   price;
    ///数量
    int64_t                  quantity;
    ///成交时间
    int64_t                  trade_time;
    ///成交金额
    double                   trade_amount;
    ///成交序号 --回报记录号
    uint64_t                 report_index;
    ///报单编号 --交易所单号
    char                     order_exch_id[XTP_ORDER_EXCH_LEN];
    ///成交类型  --成交回报中的执行类型
    TXTPTradeTypeType        trade_type;
    ///买卖方向
    XTP_SIDE_TYPE            side;
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
    char      ticker[XTP_API_TICKER_LEN];
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time;
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;  
};

///报单查询响应结构体
typedef XTPOrderInfo XTPQueryOrderRsp;


//////////////////////////////////////////////////////////////////////////
///成交回报查询
//////////////////////////////////////////////////////////////////////////
///查询成交报告请求-根据执行编号查询（保留字段）
struct XTPQueryReportByExecIdReq
{
    ///XTP订单系统ID
    uint64_t  order_xtp_id;  
    ///成交执行编号
    uint64_t  exec_id; 
};

///查询成交回报请求-查询条件
struct XTPQueryTraderReq
{
    ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      ticker[XTP_API_TICKER_LEN];
    ///开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time; 
    ///结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;  
};

///成交回报查询响应结构体
typedef XTPTradeReport  XTPQueryTradeRsp;



//////////////////////////////////////////////////////////////////////////
///账户资金查询响应结构体
//////////////////////////////////////////////////////////////////////////
struct XTPQueryAssetRsp
{
	///总资产
	double total_asset;
    ///可用资金
    double buying_power;
	///证券资产
	double security_asset;
    ///累计买入成交证券占用资金（保留字段）
    double fund_buy_amount;
    ///累计买入成交交易费用（保留字段）
    double fund_buy_fee;
    ///累计卖出成交证券所得资金（保留字段）
    double fund_sell_amount;
    ///累计卖出成交交易费用（保留字段）
    double fund_sell_fee;
};



//////////////////////////////////////////////////////////////////////////
///查询股票持仓情况
//////////////////////////////////////////////////////////////////////////
struct XTPQueryStkPositionRsp
{
    ///证券代码
    char      ticker[XTP_API_TICKER_LEN]; 
    ///证券名称
    char      ticker_name[XTP_API_TICKER_NAME_LEN]; 
    ///当前持仓
    int64_t   total_qty; 
    ///可用股份数
    int64_t   sellable_qty; 
    ///持仓成本
    double    avg_price;           
    ///浮动盈亏
    double    unrealized_pnl;        
};




#endif //_XOMS_API_STRUCT_H_

