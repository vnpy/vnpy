# encoding: UTF-8

'''
本文件中包含了CTA模块中用到的一些基础设置、类和常量等。
'''

# CTA引擎中涉及的数据类定义
from vnpy.trader.vtConstant import EMPTY_UNICODE, EMPTY_STRING, EMPTY_FLOAT, EMPTY_INT

# 常量定义
# CTA引擎中涉及到的交易方向类型
CTAORDER_BUY = u'买开'
CTAORDER_SELL = u'卖平'
CTAORDER_SHORT = u'卖开'
CTAORDER_COVER = u'买平'

# 本地停止单状态
STOPORDER_WAITING = u'等待中'
STOPORDER_CANCELLED = u'已撤销'
STOPORDER_TRIGGERED = u'已触发'

# 本地停止单前缀
STOPORDERPREFIX = 'CtaStopOrder.'

# 各类商品所在市场
NIGHT_MARKET_SQ1 = {'AU': 0, 'AG': 0}
NIGHT_MARKET_SQ2 = {'CU': 0, 'PB': 0, 'AL': 0, 'ZN': 0, 'FU': 0, 'BU': 0, 'WR': 0}
NIGHT_MARKET_SQ3 = {'RU': 0, 'RB': 0, 'HC': 0}
NIGHT_MARKET_ZZ = {'TA': 0, 'JR': 0, 'OI': 0, 'RO': 0, 'PM': 0, 'WT': 0, 'WS': 0, 'WH': 0, 'CF': 0, 'SR': 0, 'FG': 0,
                   'ME': 0, 'MA': 0, 'RS': 0, 'RM': 0, 'TC': 0, 'RI': 0, 'ER': 0}
NIGHT_MARKET_DL = {'V': 0, 'L': 0, 'BB': 0, 'I': 0, 'FB': 0, 'C': 0, 'PP': 0, 'A': 0, 'B': 0, 'M': 0, 'Y': 0, 'P': 0,
                   'JM': 0, 'J': 0}
MARKET_ZJ = {'IC': 0, 'IF': 0, 'IH': 0, 'T': 0, 'TF': 0}

# 数据库名称
SETTING_DB_NAME = 'VnTrader_Setting_Db'
POSITION_DB_NAME = 'VnTrader_Position_Db'

TICK_DB_NAME = 'VnTrader_Tick_Db'
DAILY_DB_NAME = 'VnTrader_Daily_Db'
MINUTE_DB_NAME = 'VnTrader_1Min_Db'

# 引擎类型，用于区分当前策略的运行环境
ENGINETYPE_BACKTESTING = 'backtesting'  # 回测
ENGINETYPE_TRADING = 'trading'          # 实盘

# CTA模块事件
EVENT_CTA_LOG = 'eCtaLog'               # CTA相关的日志事件
EVENT_CTA_STRATEGY = 'eCtaStrategy.'    # CTA策略状态变化事件


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