# encoding: UTF-8

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

# 本地停止单前缀
STOPORDERPREFIX = 'CtaStopOrder.'

# 各类商品所在市场
NIGHT_MARKET_SQ1 = {'AU': 0, 'AG': 0}
NIGHT_MARKET_SQ2 = {'CU': 0, 'PB': 0, 'AL': 0, 'ZN': 0, 'FU': 0, 'BU': 0, 'RB': 0, 'WR': 0, 'HC': 0}
NIGHT_MARKET_SQ3 = {'RU': 0}
NIGHT_MARKET_ZZ = {'TA': 0, 'JR': 0, 'OI': 0, 'RO': 0, 'PM': 0, 'WT': 0, 'WS': 0, 'WH': 0, 'CF': 0, 'SR': 0, 'FG': 0,
                   'ME': 0, 'MA': 0, 'RS': 0, 'RM': 0, 'TC': 0, 'RI': 0, 'ER': 0}
NIGHT_MARKET_DL = {'V': 0, 'L': 0, 'BB': 0, 'I': 0, 'FB': 0, 'C': 0, 'PP': 0, 'A': 0, 'B': 0, 'M': 0, 'Y': 0, 'P': 0,
                   'JM': 0, 'J': 0}
