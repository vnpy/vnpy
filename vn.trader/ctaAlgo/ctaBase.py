# encoding: UTF-8

'''
本文件中包含了CTA模块中用到的一些基础设置、类和常量等。
'''

from __future__ import division


# 把vn.trader根目录添加到python环境变量中
import sys
sys.path.append('..')


# 常量定义
# CTA引擎中涉及到的交易方向类型
CTAORDER_BUY = u'买开'
CTAORDER_SELL = u'卖平'
CTAORDER_SHORT = u'卖开'
CTAORDER_COVER = u'买平'

CTAORDER_OPEN_REJECT = u'开单拒绝'
CTAORDER_OPEN_FAIL = u'开单失败'
CTAORDER_CLOSE_FAIL = u'平单失败'


# 本地停止单状态
STOPORDER_WAITING = u'等待中'
STOPORDER_CANCELLED = u'已撤销'
STOPORDER_TRIGGERED = u'已触发'

# ATR 仓位管理
ATRRATE_STOPLOSS = 3
ATRRATE_YOYOLOSS = 2
ATRRATE_JUMP = 1

# 本地停止单前缀
STOPORDERPREFIX = 'CtaStopOrder.'

# 各类商品所在市场
NIGHT_MARKET_SQ1 = {'AU': 0, 'AG': 0}
NIGHT_MARKET_SQ2 = {'CU': 0, 'PB': 0, 'AL': 0, 'ZN': 0, 'FU': 0, 'BU': 0, 'WR': 0, 'HC': 0}
NIGHT_MARKET_SQ3 = {'RU': 0, 'RB': 0}
NIGHT_MARKET_ZZ = {'TA': 0, 'JR': 0, 'OI': 0, 'RO': 0, 'PM': 0, 'WT': 0, 'WS': 0, 'WH': 0, 'CF': 0, 'SR': 0, 'FG': 0,
                   'ME': 0, 'MA': 0, 'RS': 0, 'RM': 0, 'TC': 0, 'RI': 0, 'ER': 0}
NIGHT_MARKET_DL = {'V': 0, 'L': 0, 'BB': 0, 'I': 0, 'FB': 0, 'C': 0, 'PP': 0, 'A': 0, 'B': 0, 'M': 0, 'Y': 0, 'P': 0,
                   'JM': 0, 'J': 0}

# 数据库名称
SETTING_DB_NAME = 'VnTrader_Setting_Db'
TICK_DB_NAME = 'VnTrader_Tick_Db'
DAILY_DB_NAME = 'VnTrader_Daily_Db'
MINUTE_DB_NAME = 'VnTrader_1Min_Db'

# 引擎类型，用于区分当前策略的运行环境
ENGINETYPE_BACKTESTING = 'backtesting'  # 回测
ENGINETYPE_TRADING = 'trading'          # 实盘

# CTA引擎中涉及的数据类定义
from vtConstant import EMPTY_UNICODE, EMPTY_STRING, EMPTY_FLOAT, EMPTY_INT, COLOR_EQUAL

########################################################################
class StopOrder(object):
    """本地停止单"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING
        self.orderType = EMPTY_UNICODE
        self.direction = EMPTY_UNICODE
        self.offset = EMPTY_UNICODE
        self.price = EMPTY_FLOAT
        self.volume = EMPTY_INT
        
        self.strategy = None             # 下停止单的策略对象
        self.stopOrderID = EMPTY_STRING  # 停止单的本地编号 
        self.status = EMPTY_STRING       # 停止单状态


########################################################################
class CtaBarData(object):
    """K线数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING        # vt系统代码
        self.symbol = EMPTY_STRING          # 代码
        self.exchange = EMPTY_STRING        # 交易所
    
        self.open = EMPTY_FLOAT             # OHLC
        self.high = EMPTY_FLOAT
        self.low = EMPTY_FLOAT
        self.close = EMPTY_FLOAT

        self.tradingDay = EMPTY_STRING      # 交易日期
        self.date = EMPTY_STRING            # bar开始的日期（通过tick生成的bar时间，为开始时间，其他为结束时间）
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象
        
        self.volume = EMPTY_INT             # 成交量
        self.dayVolume = EMPTY_INT          # 当日累计成交量（ctp是提供这个的）
        self.openInterest = EMPTY_INT       # 持仓量
        self.color = COLOR_EQUAL          # k 线颜色,COLOR_RED，COLOR_BLUE,COLOR_EQUAL

        self.traded = False
        self.tradeStatus = EMPTY_STRING     # 当前bar的交易情况: CTAORDER_BUY 、CTAORDER_SELL、
                                            # CTAORDER_SHORT 、CTAORDER_COVER 、 CTAORDER_OPEN_REJECT 、
                                            # CTAORDER_OPEN_FAIL 、CTAORDER_CLOSE_FAIL

        self.mid4 = EMPTY_FLOAT             # (2*CLOSE+HIGH+LOW)/4;
        self.mid5 = EMPTY_FLOAT             # (2*CLOSE+HIGH+LOW+OPEN)/5

        self.seconds = EMPTY_INT            # 当前Bar的秒数（针对RenkoBar)
        self.highSeconds = -1               # 当前Bar的上限秒数
        self.lowSeconds = -1                # 当前bar的下限秒数
        self.height = EMPTY_FLOAT           # 当前Bar的高度限制（针对RenkoBar和RangeBar类）
        self.upBand = EMPTY_FLOAT           # 高位区域的基线
        self.downBand = EMPTY_FLOAT         # 低位区域的基线
        self.lowTime = None                 # 最后一次进入低位区域的时间
        self.highTime = None                # 最后一次进入高位区域的时间


########################################################################
class CtaTickData(object):
    """Tick数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""       
        self.vtSymbol = EMPTY_STRING            # vt系统代码 CF705
        self.symbol = EMPTY_STRING              # 合约代码   CF1705
        self.exchange = EMPTY_STRING            # 交易所代码

        # 成交数据
        self.lastPrice = EMPTY_FLOAT            # 最新成交价
        self.volume = EMPTY_INT                 # 最新成交量
        self.preOpenInterest = EMPTY_INT        # 昨持仓量
        self.openInterest = EMPTY_INT           # 持仓量
        
        self.upperLimit = EMPTY_FLOAT           # 涨停价
        self.lowerLimit = EMPTY_FLOAT           # 跌停价
        
        # tick的时间
        self.tradingDay = EMPTY_STRING      # 交易日期
        self.date = EMPTY_STRING            # 日期
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象
        
        # 五档行情
        self.bidPrice1 = EMPTY_FLOAT
        self.bidPrice2 = EMPTY_FLOAT
        self.bidPrice3 = EMPTY_FLOAT
        self.bidPrice4 = EMPTY_FLOAT
        self.bidPrice5 = EMPTY_FLOAT
        
        self.askPrice1 = EMPTY_FLOAT
        self.askPrice2 = EMPTY_FLOAT
        self.askPrice3 = EMPTY_FLOAT
        self.askPrice4 = EMPTY_FLOAT
        self.askPrice5 = EMPTY_FLOAT        
        
        self.bidVolume1 = EMPTY_INT
        self.bidVolume2 = EMPTY_INT
        self.bidVolume3 = EMPTY_INT
        self.bidVolume4 = EMPTY_INT
        self.bidVolume5 = EMPTY_INT
        
        self.askVolume1 = EMPTY_INT
        self.askVolume2 = EMPTY_INT
        self.askVolume3 = EMPTY_INT
        self.askVolume4 = EMPTY_INT
        self.askVolume5 = EMPTY_INT    