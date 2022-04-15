"""
General constant enums used in the trading platform.
"""

from enum import Enum


class Direction(Enum):
    """
    Direction of order/trade/position.
    """
    LONG: str = "多"
    SHORT: str = "空"
    NET: str = "净"


class Offset(Enum):
    """
    Offset of order/trade.
    """
    NONE: str = ""
    OPEN: str = "开"
    CLOSE: str = "平"
    CLOSETODAY: str = "平今"
    CLOSEYESTERDAY: str = "平昨"


class Status(Enum):
    """
    Order status.
    """
    SUBMITTING: str = "提交中"
    NOTTRADED: str = "未成交"
    PARTTRADED: str = "部分成交"
    ALLTRADED: str = "全部成交"
    CANCELLED: str = "已撤销"
    REJECTED: str = "拒单"


class Product(Enum):
    """
    Product class.
    """
    EQUITY: str = "股票"
    FUTURES: str = "期货"
    OPTION: str = "期权"
    INDEX: str = "指数"
    FOREX: str = "外汇"
    SPOT: str = "现货"
    ETF: str = "ETF"
    BOND: str = "债券"
    WARRANT: str = "权证"
    SPREAD: str = "价差"
    FUND: str = "基金"


class OrderType(Enum):
    """
    Order type.
    """
    LIMIT: str = "限价"
    MARKET: str = "市价"
    STOP: str = "STOP"
    FAK: str = "FAK"
    FOK: str = "FOK"
    RFQ: str = "询价"


class OptionType(Enum):
    """
    Option type.
    """
    CALL: str = "看涨期权"
    PUT: str = "看跌期权"


class Exchange(Enum):
    """
    Exchange.
    """
    # Chinese
    CFFEX: str = "CFFEX"         # China Financial Futures Exchange
    SHFE: str = "SHFE"           # Shanghai Futures Exchange
    CZCE: str = "CZCE"           # Zhengzhou Commodity Exchange
    DCE: str = "DCE"             # Dalian Commodity Exchange
    INE: str = "INE"             # Shanghai International Energy Exchange
    SSE: str = "SSE"             # Shanghai Stock Exchange
    SZSE: str = "SZSE"           # Shenzhen Stock Exchange
    BSE: str = "BSE"             # Beijing Stock Exchange
    SGE: str = "SGE"             # Shanghai Gold Exchange
    WXE: str = "WXE"             # Wuxi Steel Exchange
    CFETS: str = "CFETS"         # CFETS Bond Market Maker Trading System
    XBOND: str = "XBOND"         # CFETS X-Bond Anonymous Trading System

    # Global
    SMART: str = "SMART"         # Smart Router for US stocks
    NYSE: str = "NYSE"           # New York Stock Exchnage
    NASDAQ: str = "NASDAQ"       # Nasdaq Exchange
    ARCA: str = "ARCA"           # ARCA Exchange
    EDGEA: str = "EDGEA"         # Direct Edge Exchange
    ISLAND: str = "ISLAND"       # Nasdaq Island ECN
    BATS: str = "BATS"           # Bats Global Markets
    IEX: str = "IEX"             # The Investors Exchange
    NYMEX: str = "NYMEX"         # New York Mercantile Exchange
    COMEX: str = "COMEX"         # COMEX of CME
    GLOBEX: str = "GLOBEX"       # Globex of CME
    IDEALPRO: str = "IDEALPRO"   # Forex ECN of Interactive Brokers
    CME: str = "CME"             # Chicago Mercantile Exchange
    ICE: str = "ICE"             # Intercontinental Exchange
    SEHK: str = "SEHK"           # Stock Exchange of Hong Kong
    HKFE: str = "HKFE"           # Hong Kong Futures Exchange
    SGX: str = "SGX"             # Singapore Global Exchange
    CBOT: str = "CBT"            # Chicago Board of Trade
    CBOE: str = "CBOE"           # Chicago Board Options Exchange
    CFE: str = "CFE"             # CBOE Futures Exchange
    DME: str = "DME"             # Dubai Mercantile Exchange
    EUREX: str = "EUX"           # Eurex Exchange
    APEX: str = "APEX"           # Asia Pacific Exchange
    LME: str = "LME"             # London Metal Exchange
    BMD: str = "BMD"             # Bursa Malaysia Derivatives
    TOCOM: str = "TOCOM"         # Tokyo Commodity Exchange
    EUNX: str = "EUNX"           # Euronext Exchange
    KRX: str = "KRX"             # Korean Exchange
    OTC: str = "OTC"             # OTC Product (Forex/CFD/Pink Sheet Equity)
    IBKRATS: str = "IBKRATS"     # Paper Trading Exchange of IB

    # Special Function
    LOCAL: str = "LOCAL"         # For local generated data


class Currency(Enum):
    """
    Currency.
    """
    USD: str = "USD"
    HKD: str = "HKD"
    CNY: str = "CNY"


class Interval(Enum):
    """
    Interval of bar data.
    """
    MINUTE: str = "1m"
    HOUR: str = "1h"
    DAILY: str = "d"
    WEEKLY: str = "w"
    TICK: str = "tick"
