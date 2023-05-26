"""
General constant string used in VN Trader.
"""

from enum import Enum


class AccType(Enum):
    """账户类型"""
    Normal = '普通'
    Credit = '信用'


class AssetsType(Enum):
    """资产类型、持仓类型"""
    Normal = '普通'
    LoanBuy = '融资'
    LoanSell = '融券'


class Direction(Enum):
    """
    Direction of order/trade/position.
    """
    LONG = "多"
    SHORT = "空"
    NET = "净"
    PURCHASE = '申购'
    REDEMPTION = '赎回'
    BUY_BASKET = '买篮子'
    SELL_BASKET = '卖篮子'
    LoanBuy = "融资买入"
    LoanSell = "融券卖出"
    PreBookLoanSell = "专融卖出"
    EnBuyBack = "买券还券"
    EnSellBack = "卖券还款"
    PayBack = "直接还款"
    StockBack = "直接还券"
    NONE = 'NONE'


class Offset(Enum):
    """
    Offset of order/trade.
    """
    NONE = ""
    OPEN = "开"
    CLOSE = "平"
    CLOSETODAY = "平今"
    CLOSEYESTERDAY = "平昨"


class Status(Enum):
    """
    Order status.
    """
    SUBMITTING = "提交中"
    NOTTRADED = "未成交"
    PARTTRADED = "部分成交"
    ALLTRADED = "全部成交"
    CANCELLED = "已撤销"
    PARTTRADED_CANCELLED = "部成余撤"
    CANCELING = "撤销已报"
    REJECTED = "拒单"


class Product(Enum):
    """
    Product class.
    """
    EQUITY = "股票"
    FUTURES = "期货"
    OPTION = "期权"
    INDEX = "指数"
    FOREX = "外汇"
    SPOT = "现货"
    ETF = "ETF"
    BOND = "债券"
    WARRANT = "权证"
    SPREAD = "价差"
    FUND = "基金"
    BASKET = "篮子"
    OTHERS = "其他"


class OrderType(Enum):
    """
    Order type.
    """
    LIMIT = "限价"
    MARKET = "市价"
    STOP = "STOP"
    FAK = "FAK"
    FOK = "FOK"
    RFQ = "询价"
    BestOrLimit = "最优五转限价"


class OptionType(Enum):
    """
    Option type.
    """
    CALL = "看涨期权"
    PUT = "看跌期权"


class Exchange(Enum):
    """
    Exchange.
    """
    # Chinese
    CFFEX = "CFFEX"         # China Financial Futures Exchange
    SHFE = "SHFE"           # Shanghai Futures Exchange
    CZCE = "CZCE"           # Zhengzhou Commodity Exchange
    DCE = "DCE"             # Dalian Commodity Exchange
    INE = "INE"             # Shanghai International Energy Exchange
    SSE = "SSE"             # Shanghai Stock Exchange
    SHO = "SHO"
    SZSE = "SZSE"           # Shenzhen Stock Exchange
    SZO = "SZO"
    SGE = "SGE"             # Shanghai Gold Exchange
    WXE = "WXE"             # Wuxi Steel Exchange
    CFETS = "CFETS"         # CFETS Bond Market Maker Trading System
    XBOND = "XBOND"         # CFETS X-Bond Anonymous Trading System
    GFEX = "GFEX"

    # Global
    SMART = "SMART"         # Smart Router for US stocks
    NYSE = "NYSE"           # New York Stock Exchnage
    NASDAQ = "NASDAQ"       # Nasdaq Exchange
    ARCA = "ARCA"           # ARCA Exchange
    EDGEA = "EDGEA"         # Direct Edge Exchange
    ISLAND = "ISLAND"       # Nasdaq Island ECN
    BATS = "BATS"           # Bats Global Markets
    IEX = "IEX"             # The Investors Exchange
    NYMEX = "NYMEX"         # New York Mercantile Exchange
    COMEX = "COMEX"         # COMEX of CME
    GLOBEX = "GLOBEX"       # Globex of CME
    IDEALPRO = "IDEALPRO"   # Forex ECN of Interactive Brokers
    CME = "CME"             # Chicago Mercantile Exchange
    ICE = "ICE"             # Intercontinental Exchange
    SEHK = "SEHK"           # Stock Exchange of Hong Kong
    HKFE = "HKFE"           # Hong Kong Futures Exchange
    HKSE = "HKSE"           # Hong Kong Stock Exchange
    SGX = "SGX"             # Singapore Global Exchange
    CBOT = "CBT"            # Chicago Board of Trade
    CBOE = "CBOE"           # Chicago Board Options Exchange
    CFE = "CFE"             # CBOE Futures Exchange
    DME = "DME"             # Dubai Mercantile Exchange
    EUREX = "EUX"           # Eurex Exchange
    APEX = "APEX"           # Asia Pacific Exchange
    LME = "LME"             # London Metal Exchange
    BMD = "BMD"             # Bursa Malaysia Derivatives
    TOCOM = "TOCOM"         # Tokyo Commodity Exchange
    EUNX = "EUNX"           # Euronext Exchange
    KRX = "KRX"             # Korean Exchange
    OTC = "OTC"             # OTC Product (Forex/CFD/Pink Sheet Equity)
    IBKRATS = "IBKRATS"     # Paper Trading Exchange of IB

    # CryptoCurrency
    BITMEX = "BITMEX"
    OKEX = "OKEX"
    HUOBI = "HUOBI"
    BITFINEX = "BITFINEX"
    BINANCE = "BINANCE"
    BYBIT = "BYBIT"
    COINBASE = "COINBASE"
    DERIBIT = "DERIBIT"
    GATEIO = "GATEIO"
    BITSTAMP = "BITSTAMP"
    DYDX = "DYDX"
    FTX = "FTX"

    # Special Function
    LOCAL = "LOCAL"         # For local generated data
    LOCAL_BASKET = "LOCAL_BASKET"       # 本地篮子
    BASKET = 'BASKET'                   # gateway提供的篮子


class Currency(Enum):
    """
    Currency.
    """
    USD = "USD"
    HKD = "HKD"
    CNY = "CNY"
    CNH = "CNH"
    EUR = "EUR"
    OTHERS = 'OTHERS'


class Interval(Enum):
    """
    Interval of bar data.
    """
    MINUTE = "1m"
    HOUR = "1h"
    DAILY = "d"
    WEEKLY = "w"
    TICK = "tick"


class ProductStatus(Enum):
    NONE = '正常'
    B = '停牌'
    M = '暂时熔断'
    N = '今日熔断'
    P = '暂停交易'

