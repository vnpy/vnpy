"""
General constant string used in VN Trader.
"""
from enum import Enum


class Direction(Enum):
    LONG = "多"
    SHORT = "空"
    NET = "净"


class Offset(Enum):
    OPEN = "开"
    CLOSE = "平"
    CLOSE_TODAY = "平今"
    CLOSE_YESTERDAY = "平昨"


class Status(Enum):
    SUBMITTING = "提交中"
    NOTTRADED = "未成交"
    PARTTRADED = "部分成交"
    ALLTRADED = "全部成交"
    CANCELLED = "已撤销"
    REJECTED = "拒单"
    UNDEFINED = "未定义"


class Product(Enum):
    EQUITY = "股票"
    FUTURES = "期货"
    OPTION = "期权"
    INDEX = "指数"
    FOREX = "外汇"
    SPOT = "现货"
    ETF = "ETF"
    BOND = "债券"
    WARRANT = "权证"


class PriceType(Enum):
    LIMIT = "限价"
    MARKET = "市价"
    FAK = "FAK"
    FOK = "FOK"


class Option(Enum):
    CALL = "看涨期权"
    PUT = "看跌期权"


class Exchange(Enum):
    SSE = "SSE"
    SZSE = "SZSE"
    CFFEX = "CFFEX"
    SHFE = "SHFE"
    CZCE = "CZCE"
    DCE = "DCE"
    INE = "INE"
    SGE = "SGE"
    SMART = "SMART"
    NYMEX = "NYMEX"
    GLOBEX = "GLOBEX"
    IDEALPRO = "IDEALPRO"
    CME = "CME"
    ICE = "ICE"
    SEHK = "SEHK"
    HKFE = "HKFE"


class Currency(Enum):
    USD = "USD"
    HKD = "HKD"
    CNY = "CNY"


class Interval(Enum):
    M1 = "1分钟"
    M4 = "5分钟"
    M15 = "15分钟"
    M30 = "30分钟"
    H1 = "1小时"
    H4 = "4小时"
    DAILY = "日线"
    WEEKLY = "周线"
