/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xquote_api_struct.h
///@brief 定义行情类相关数据结构
/////////////////////////////////////////////////////////////////////////
#ifndef _XQUOTE_API_STRUCT_H_
#define _XQUOTE_API_STRUCT_H_

#include <stdint.h>
#include "xtp_api_data_type.h"

#pragma pack(8)

///指定的合约
typedef struct XTPSpecificTickerStruct
{
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息）例如"600000"，不带空格，以'\0'结尾
	char	ticker[XTP_TICKER_LEN];
} XTPST;


///行情
typedef struct XTPMarketDataStruct
{
    // 代码
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息），不带空格，以'\0'结尾
    char	ticker[XTP_TICKER_LEN];

    // 股票等价格
	///最新价
	double	last_price;
	///昨收盘
	double	pre_close_price;
	///今开盘
	double	open_price;
	///最高价
	double	high_price;
	///最低价
	double	low_price;
    ///今收盘
    double	close_price;

    // 期货等数据
    ///昨持仓量（目前未填写）
    double	pre_open_interest;
    ///持仓量（目前未填写）
	double	open_interest;
    ///上次结算价（目前未填写）
    double	pre_settlement_price;
    ///本次结算价（目前未填写）
	double	settlement_price;

	///涨停板价（目前未填写）
	double	upper_limit_price;
	///跌停板价（目前未填写）
	double	lower_limit_price;
	///昨虚实度（目前未填写）
	double	pre_delta;
	///今虚实度（目前未填写）
	double	curr_delta;

    /// 时间类，格式为YYYYMMDDHHMMSSsss
    int64_t data_time;

    // 量额数据
    ///数量，为总成交量（单位股，与交易所一致）
    int64_t	qty;
    ///成交金额，为总成交金额（单位元，与交易所一致）
    double	turnover;
    ///当日均价=(turnover/qty)
    double	avg_price;

    // 买卖盘
    ///十档申买价
    double bid[10];
    ///十档申卖价
    double	ask[10];
    ///十档申买量
    int64_t	bid_qty[10];
    ///十档申卖量
    int64_t	ask_qty[10];

    // 额外数据（以下数据目前未填写）
    ///成交笔数
    int64_t trades_count;
    ///当前交易状态说明
    char ticker_status[8];
    ///委托买入总量
    int64_t total_bid_qty;
    ///委托卖出总量
    int64_t total_ask_qty;
    ///加权平均委买价格
    double ma_bid_price;
    ///加权平均委卖价格
    double ma_ask_price;
    ///债券加权平均委买价格
    double ma_bond_bid_price;
    ///债券加权平均委卖价格
    double ma_bond_ask_price;
    ///债券到期收益率
    double yield_to_maturity;
    ///ETF净值估值
    double iopv;
    ///ETF申购笔数
    int32_t etf_buy_count;
    ///ETF赎回笔数
    int32_t etf_sell_count;
    ///ETF申购数量
    double etf_buy_qty;
    ///ETF申购金额
    double etf_buy_money;
    ///ETF赎回数量
    double etf_sell_qty;
    ///ETF赎回金额
    double etf_sell_money;
    ///权证执行的总数量
    double total_warrant_exec_qty;
    ///权证跌停价格（元）
    double warrant_lower_price;
    ///权证涨停价格（元）
    double warrant_upper_price;
    ///买入撤单笔数
    int32_t cancel_buy_count;
    ///卖出撤单笔数
    int32_t cancel_sell_count;
    ///买入撤单数量
    double cancel_buy_qty;
    ///卖出撤单数量
    double cancel_sell_qty;
    ///买入撤单金额
    double cancel_buy_money;
    ///卖出撤单金额
    double cancel_sell_money;
    ///买入总笔数
    int64_t total_buy_count;
    ///卖出总笔数
    int64_t total_sell_count;
    ///买入委托成交最大等待时间
    int32_t duration_after_buy;
    ///卖出委托成交最大等待时间
    int32_t duration_after_sell;
    ///买方委托价位数
    int32_t num_bid_orders;
    ///卖方委托价位数
    int32_t num_ask_orders;
    ///成交时间（UA3113）
    int32_t exec_time;
    ///闭市标志（UA103/UA104）
    char is_market_closed[4];
    ///合约持仓量（UA103）
    double total_position;
    ///市盈率1（UA103）
    double pe_ratio1;
    ///市盈率2（UA103）
    double pe_ratio2;
} XTPMD;


///股票行情静态信息
typedef struct XTPQuoteStaticInfo {
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息），不带空格，以'\0'结尾
    char    ticker[XTP_TICKER_LEN];
    /// 合约名称
    char    ticker_name[XTP_TICKER_NAME_LEN];
    /// 合约类型
	XTP_TICKER_TYPE ticker_type;
    ///昨收盘
    double  pre_close_price;
    ///涨停板价
    double  upper_limit_price;
    ///跌停板价
    double  lower_limit_price;
	///最小变动价位
	double  price_tick;
    /// 合约最小交易量(买)
    int32_t  buy_qty_unit;
    /// 合约最小交易量(卖)
	int32_t sell_qty_unit;
} XTPQSI;


///定单薄
typedef struct OrderBookStruct {
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息），不带空格，以'\0'结尾
    char    ticker[XTP_TICKER_LEN];

    ///最新价
    double last_price;
    ///数量，为总成交量
    int64_t qty;
    ///成交金额，为总成交金额
    double  turnover;
    ///成交笔数
    int64_t trades_count;

    // 买卖盘
    ///十档申买价
    double bid[10];
    ///十档申卖价
    double  ask[10];
    ///十档申买量
    int64_t bid_qty[10];
    ///十档申卖量
    int64_t ask_qty[10];
    /// 时间类
    int64_t data_time;
} XTPOB;

////////////////////////////////// 逐笔数据


///逐笔委托(仅适用深交所)
struct XTPTickByTickEntrust {
    ///频道代码
    int32_t channel_no;
    ///委托序号(在同一个channel_no内唯一，从1开始连续)
    int64_t seq;
    ///委托价格
    double  price;
    ///委托数量
    int64_t qty;
    ///'1':买; '2':卖; 'G':借入; 'F':出借
    char  side;
    ///订单类别: '1': 市价; '2': 限价; '3': 本方最优
    char ord_type;
};

///逐笔成交
struct XTPTickByTickTrade {
    ///频道代码
    int32_t channel_no;
    ///委托序号(在同一个channel_no内唯一，从1开始连续)
    int64_t seq;
    ///成交价格
    double price;
    ///成交量
    int64_t qty;
    ///成交金额(仅适用上交所)
    double money;
    ///买方订单号
    int64_t bid_no;
    ///卖方订单号
    int64_t ask_no;
    /// SH: 内外盘标识('B':主动买; 'S':主动卖; 'N':未知)
    /// SZ: 成交标识('4':撤; 'F':成交)
    char trade_flag;
};

///逐笔数据信息
typedef struct XTPTickByTickStruct {
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息），不带空格，以'\0'结尾
    char ticker[XTP_TICKER_LEN];
    ///预留
    int64_t seq;
    ///委托时间 or 成交时间
    int64_t data_time;
    ///委托 or 成交
    XTP_TBT_TYPE type;

    union {
        XTPTickByTickEntrust entrust;
        XTPTickByTickTrade     trade;
    };
} XTPTBT;


///供查询的最新信息
typedef struct XTPTickerPriceInfo {
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息），不带空格，以'\0'结尾
    char ticker[XTP_TICKER_LEN];
    ///最新价
    double last_price;
} XTPTPI;


#pragma pack()

#endif
