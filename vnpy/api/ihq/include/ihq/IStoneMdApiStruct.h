#pragma once
#include "IStoneApiDataType.h"

namespace istone
{
	namespace mdapi
	{
		///用户登录请求
		struct CIStoneReqUserLogin
		{
			char	TradingDay[ISTONE_TRADING_DAY_LEN];		//交易日
			char	UserID[ISTONE_USERID_LEN];				//交易用户代码
			char	Password[ISTONE_USER_PW_LEN];			//密码
			char	UserProductInfo[41];					//用户端产品信息
			char	IPAddress[30];							//IP地址
			char	MacAddress[30];							//Mac地址
		};

		///用户登录应答
		struct CIStoneRspUserLogin
		{
			char	TradingDay[ISTONE_TRADING_DAY_LEN];		//交易日
			char	UserID[ISTONE_USERID_LEN];				//交易用户代码
			int		MaxUserOrderLocalID;					//用户最大本地报单号
			char	LoginTime[ISTONE_TIMESTAMP_LEN];		//登录成功时间
			ISTONE_USERS_TYPE    userType;                  //用户类型
		};

		///用户登出请求
		struct CIStoneReqUserLogout
		{
			char	UserID[ISTONE_USERID_LEN];				//交易用户代码
		};

		///用户登出应答
		struct CIStoneRspUserLogout
		{
			char	UserID[ISTONE_USERID_LEN];				//交易用户代码
		};

		///用户订阅快照行情应答
		struct CIStoneSubParams
		{
			int TickType;					//股票类型
			int ExchangeType;				//交易所代码
		};

		///用户逐笔行情应答
		struct CIStoneRspSubTickByTick 
		{
			int16_t SubAllFlag;								//全部订阅
			ISTONE_EXCHANGE_TYPE ExchangeID;				// 交易所代码
			char	Ticker[ISTONE_TICKER_LEN];				//合约代码
		};
		///用户逐笔行情应答
		struct CIStoneRspUnSubTickByTick
		{
			int16_t UnSubAllFlag;								//全部订阅
			ISTONE_EXCHANGE_TYPE ExchangeID;				// 交易所代码
			char	Ticker[ISTONE_TICKER_LEN];				//合约代码		
		};


		///响应信息
		struct CIStoneRspInfo
		{
			int	Tid;										//业务ID
			int	ErrorID;									//错误代码
			TIStoneErrorMsgType	ErrorMsg;					//错误信息
		};

		enum ISTONE_MARKETDATA_TYPE 
		{
			ISTONE_MARKETDATA_ACTUAL = 0,					// 现货(股票/基金/债券等)
			ISTONE_MARKETDATA_OPTION = 1,					// 期权
		};

		///实时行情查询请求
		struct CIStoneQryMarketData
		{
			ISTONE_EXCHANGE_TYPE	ExchangeID;		//交易所代码
			char	Ticker[ISTONE_TICKER_LEN];		//合约代码
		};

		struct CIStoneSpecificTicker
		{
			ISTONE_EXCHANGE_TYPE ExchangeID;				// 交易所代码
			char	Ticker[ISTONE_TICKER_LEN];				//合约代码
		};

		///股票、基金、债券等额外数据
		struct CIStoneMarketDataStockExData 
		{
			///委托买入总量(SH,SZ)
			int64_t TotalBidQty;
			///委托卖出总量(SH,SZ)
			int64_t TotalAskQty;
			///加权平均委买价格(SH,SZ)
			double MaBidPrice;
			///加权平均委卖价格(SH,SZ)
			double MaAskPrice;
			///债券加权平均委买价格(SH)
			double MaBondBidPrice;
			///债券加权平均委卖价格(SH)
			double MaBondAskPrice;
			///债券到期收益率(SH)
			double YieldToMaturity;
			///基金实时参考净值(SH,SZ)
			double Iopv;
			///ETF申购笔数(SH)
			int32_t EtfBuyCount;
			///ETF赎回笔数(SH)
			int32_t EtfSellCount;
			///ETF申购数量(SH)
			double EtfBuyQty;
			///ETF申购金额(SH)
			double EtfBuyMoney;
			///ETF赎回数量(SH)
			double EtfSellQty;
			///ETF赎回金额(SH)
			double EtfSellMoney;
			///权证执行的总数量(SH)
			double TotalWarrantExecQty;
			///权证跌停价格（元）(SH)
			double WarrantLowerPrice;
			///权证涨停价格（元）(SH)
			double WarrantUpperPrice;
			///买入撤单笔数(SH)
			int32_t CancelBuyCount;
			///卖出撤单笔数(SH)
			int32_t CancelSellCount;
			///买入撤单数量(SH)
			double CancelBuyQty;
			///卖出撤单数量(SH)
			double CancelSellQty;
			///买入撤单金额(SH)
			double CancelBuyMoney;
			///卖出撤单金额(SH)
			double CancelSellMoney;
			///买入总笔数(SH)
			int64_t TotalBuyCount;
			///卖出总笔数(SH)
			int64_t TotalSellCount;
			///买入委托成交最大等待时间(SH)
			int32_t DurationAfterBuy;
			///卖出委托成交最大等待时间(SH)
			int32_t DurationAfterSell;
			///买方委托价位数(SH)
			int32_t NumBidOrders;
			///卖方委托价位数(SH)
			int32_t NumAskOrders;

			///基金T-1日净值(SZ)
			double PreIopv;
			///预留
			int64_t R1;
			///预留
			int64_t R2;
		};

		// 期权额外数据
		struct CIStoneMarketDataOptionExData 
		{
			///波段性中断参考价(SH)
			double  AuctionPrice;
			///波段性中断集合竞价虚拟匹配量(SH)
			int64_t AuctionQty;
			///最近询价时间(SH)
			int64_t LastEnquiryTime;
		};

		///一档50笔委托行情
		struct CIStoneTickerBid1
		{
			uint32_t			Bid1NumOfOrders;			// 买一档价位总委托笔数
			uint8_t				Bid1NoOrders;				// 买一档价位揭示委托笔数
			uint32_t			Bid1Orders[50];				// 买一档50笔委托
			uint32_t			Ask1NumOfOrders;			// 卖一档价位总委托笔数
			uint8_t				Ask1NoOrders;				// 卖一档价位揭示委托笔数
			uint32_t			Ask1Orders[50];				// 卖一档50笔委托
		};

		///深度行情
		struct CIStoneDepthMarketData
		{
			//交易所代码
			ISTONE_EXCHANGE_TYPE ExchangeID;
			/// 合约类型
			ISTONE_TICKER_TYPE TickerType;
			///合约代码（不包含交易所信息），不带空格，以'\0'结尾
			char	Ticker[ISTONE_TICKER_LEN];

			///最新价
			double	LastPrice;
			///昨收盘
			double	PreClosePrice;
			///今开盘
			double	OpenPrice;
			///最高价
			double	HighestPrice;
			///最低价
			double	LowestPrice;
			///今收盘
			double	ClosePrice;

			// 期权数据
			///昨日持仓量(张)(目前未填写)
			int64_t PreOpenInterest;
			///持仓量(张)
			int64_t	OpenInterest;
			///昨日结算价
			double	PreSettlementPrice;
			///今日结算价
			double	SettlementPrice;

			///昨虚实度
			double	PreDelta;
			///今虚实度
			double	CurrDelta;
			///涨停板价
			double	UpperLimitPrice;
			///跌停板价
			double	LowerLimitPrice;

			/// 时间类，格式为YYYYMMDDHHMMSSsss
			int64_t DateTime;

			// 量额数据
			///数量，为总成交量（单位股，与交易所一致）
			int64_t		Qty;
			///成交金额，为总成交金额（单位元，与交易所一致）
			double	Turnover;
			///当日均价=(turnover/qty)
			double	AvgPrice;

			// 买卖盘
			///十档申买价
			double Bid[10];
			///十档申卖价
			double	Ask[10];
			///十档申买量
			int64_t	BidQty[10];
			///十档申卖量
			int64_t	AskQty[10];
			///成交笔数
			int64_t TradesCount;
			///当前交易状态说明
			char TickerStatus[8];

			//一档50笔委托
			CIStoneTickerBid1 tickBid1;

			///决定了union是哪种数据类型
			ISTONE_MARKETDATA_TYPE DataType;
			// 额外数据
			///数据
			union {
				CIStoneMarketDataStockExData  Stk;
				CIStoneMarketDataOptionExData Opt;
			};
			///预留
			int32_t R4;
		};

		///股票行情静态信息
		struct CIStoneQuoteStaticInfo 
		{
			///交易所代码
			ISTONE_EXCHANGE_TYPE ExchangeID;
			///合约代码（不包含交易所信息），不带空格，以'\0'结尾
			char    Ticker[ISTONE_TICKER_LEN];
			/// 合约名称
			char    TickerName[ISTONE_TICKER_NAME_LEN];
			/// 合约类型
			ISTONE_TICKER_TYPE TickerType;
			///昨收盘
			double  PreClosePrice;
			///涨停板价
			double  UpperLimitPrice;
			///跌停板价
			double  LowerLimitPrice;
			///最小变动价位
			double  PriceTick;
			/// 合约最小交易量(买)
			int32_t  BuyQtyUnit;
			/// 合约最小交易量(卖)
			int32_t SellQtyUnit;
		};


		///定单薄（仅适用于深交所）
		struct CIStoneOrderBook 
		{
			///交易所代码
			ISTONE_EXCHANGE_TYPE ExchangeID;
			///合约代码（不包含交易所信息），不带空格，以'\0'结尾
			char    Ticker[ISTONE_TICKER_LEN];

			///最新价
			double LastPrice;
			///数量，为总成交量
			int64_t Qty;
			///成交金额，为总成交金额
			double  Turnover;
			///成交笔数
			int64_t TradesCount;

			// 买卖盘
			///十档申买价
			double Bid[10];
			///十档申卖价
			double  Ask[10];
			///十档申买量
			int64_t BidQty[10];
			///十档申卖量
			int64_t AskQty[10];
			/// 时间类
			int64_t DataTime;

			///缓存十档对应的序列号
			string bidSeq[10];
			string askSeq[10];
		};

		////////////////////////////////// 逐笔数据


		///逐笔委托(仅适用深交所)
		struct CIStoneTickByTickEntrust 
		{
			///频道代码
			int32_t ChannalNo;
			///委托序号(在同一个channel_no内唯一，从1开始连续)
			int64_t Seq;
			///委托价格
			double  Price;
			///委托数量
			int64_t Qty;
			///'1':买; '2':卖; 'G':借入; 'F':出借
			char  Side;
			///订单类别: '1': 市价; '2': 限价; 'U': 本方最优
			char OrdType;
		};

		///逐笔成交
		struct CIStoneTickByTickTrade 
		{
			///频道代码
			int32_t ChannalNo;
			///委托序号(在同一个channel_no内唯一，从1开始连续)
			int64_t Seq;
			///成交价格
			double Price;
			///成交量
			int64_t Qty;
			///成交金额(仅适用上交所)
			double Money;
			///买方订单号
			int64_t BidNo;
			///卖方订单号
			int64_t AskNo;
			/// SH: 内外盘标识('B':主动买; 'S':主动卖; 'N':未知)
			/// SZ: 成交标识('4':撤; 'F':成交)
			char TradeFlag;
		};

		///逐笔数据信息
		struct CIStoneTickByTick 
		{
			///交易所代码
			ISTONE_EXCHANGE_TYPE ExchangeID;
			///合约代码（不包含交易所信息），不带空格，以'\0'结尾
			char Ticker[ISTONE_TICKER_LEN];
			///预留
			int64_t Seq;
			///委托时间 or 成交时间
			int64_t DataTime;
			///委托 or 成交
			ISTONE_TBT_TYPE Type;

			union {
				CIStoneTickByTickEntrust Entrust;
				CIStoneTickByTickTrade   Trade;
			};
		};

		///供查询的最新信息
		struct CIStoneTickerPriceInfo 
		{
			///交易所代码
			ISTONE_EXCHANGE_TYPE ExchangeID;
			///合约代码（不包含交易所信息），不带空格，以'\0'结尾
			char Ticker[ISTONE_TICKER_LEN];
			///最新价
			double LastPrice;
		};
	}
}
