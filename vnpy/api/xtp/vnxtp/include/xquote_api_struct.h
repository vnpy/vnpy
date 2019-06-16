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

///股票、基金、债券等额外数据
struct XTPMarketDataStockExData {
    ///委托买入总量(SH,SZ)
    int64_t total_bid_qty;
    ///委托卖出总量(SH,SZ)
    int64_t total_ask_qty;
    ///加权平均委买价格(SH,SZ)
    double ma_bid_price;
    ///加权平均委卖价格(SH,SZ)
    double ma_ask_price;
    ///债券加权平均委买价格(SH)
    double ma_bond_bid_price;
    ///债券加权平均委卖价格(SH)
    double ma_bond_ask_price;
    ///债券到期收益率(SH)
    double yield_to_maturity;
    ///基金实时参考净值(SH,SZ)
    double iopv;
    ///ETF申购笔数(SH)
    int32_t etf_buy_count;
    ///ETF赎回笔数(SH)
    int32_t etf_sell_count;
    ///ETF申购数量(SH)
    double etf_buy_qty;
    ///ETF申购金额(SH)
    double etf_buy_money;
    ///ETF赎回数量(SH)
    double etf_sell_qty;
    ///ETF赎回金额(SH)
    double etf_sell_money;
    ///权证执行的总数量(SH)
    double total_warrant_exec_qty;
    ///权证跌停价格（元）(SH)
    double warrant_lower_price;
    ///权证涨停价格（元）(SH)
    double warrant_upper_price;
    ///买入撤单笔数(SH)
    int32_t cancel_buy_count;
    ///卖出撤单笔数(SH)
    int32_t cancel_sell_count;
    ///买入撤单数量(SH)
    double cancel_buy_qty;
    ///卖出撤单数量(SH)
    double cancel_sell_qty;
    ///买入撤单金额(SH)
    double cancel_buy_money;
    ///卖出撤单金额(SH)
    double cancel_sell_money;
    ///买入总笔数(SH)
    int64_t total_buy_count;
    ///卖出总笔数(SH)
    int64_t total_sell_count;
    ///买入委托成交最大等待时间(SH)
    int32_t duration_after_buy;
    ///卖出委托成交最大等待时间(SH)
    int32_t duration_after_sell;
    ///买方委托价位数(SH)
    int32_t num_bid_orders;
    ///卖方委托价位数(SH)
    int32_t num_ask_orders;

    ///基金T-1日净值(SZ)
    double pre_iopv;
    ///预留
    int64_t r1;
    ///预留
    int64_t r2;
};

/// 期权额外数据
struct XTPMarketDataOptionExData {
    ///波段性中断参考价(SH)
    double  auction_price;
    ///波段性中断集合竞价虚拟匹配量(SH)
    int64_t auction_qty;
    ///最近询价时间(SH)
    int64_t last_enquiry_time;
};

/////////////////////////////////////////////////////////////////////////
///@brief XTP_MARKETDATA_TYPE是行情快照数据类型
/////////////////////////////////////////////////////////////////////////
enum XTP_MARKETDATA_TYPE {
    XTP_MARKETDATA_ACTUAL = 0, // 现货(股票/基金/债券等)
    XTP_MARKETDATA_OPTION = 1, // 期权
};

///行情
typedef struct XTPMarketDataStruct
{
    // 代码
    ///交易所代码
    XTP_EXCHANGE_TYPE exchange_id;
    ///合约代码（不包含交易所信息），不带空格，以'\0'结尾
    char	ticker[XTP_TICKER_LEN];

    // 价格
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

    // 期权数据
    ///昨日持仓量(张)(目前未填写)
    int64_t pre_total_long_positon;
    ///持仓量(张)
	int64_t	total_long_positon;
    ///昨日结算价
    double	pre_settl_price;
    ///今日结算价
	double	settl_price;

	// 涨跌停
	///涨停价
	double	upper_limit_price;
	///跌停价
	double	lower_limit_price;
	///预留
	double	pre_delta;
	///预留
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

    // 额外数据
    ///成交笔数
    int64_t trades_count;
    ///当前交易状态说明
    char ticker_status[8];
    ///数据
    union {
        XTPMarketDataStockExData  stk;
        XTPMarketDataOptionExData opt;
    } ;
    ///决定了union是哪种数据类型
    XTP_MARKETDATA_TYPE data_type;
    ///预留
    int32_t r4;
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
    ///订单类别: '1': 市价; '2': 限价; 'U': 本方最优
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
