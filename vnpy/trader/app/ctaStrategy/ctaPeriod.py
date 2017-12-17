# encoding: UTF-8

# 周期类，定义CTA的五种周期，及其周期变换矩阵

from vnpy.trader.vtConstant import *
from datetime import datetime

PERIOD_INIT = u'init'               # 初始状态
PERIOD_LONG = u'long'               # 周期方向做多
PERIOD_SHORT = u'short'             # 周期方向做空
PERIOD_SHOCK = u'shock'             # 震荡周期
PERIOD_LONG_EXTREME = u'long_ext'   # 周期方向极端做多
PERIOD_SHORT_EXTREME = u'short_ext' # 周期方向极端做空

class CtaPeriod(object):
    """CTA 周期"""

    def __init__(self, mode, price, pre_mode=PERIOD_INIT, dt=datetime.now()):
        """初始化函数"""
        self.open = price         # 开始价格
        self.close = price        # 结束价格
        self.high = price         # 最高价格
        self.low = price          # 最低价格

        self.mode = mode         # 周期模式 PERIOD_XXX

        self.pre_mode = pre_mode      # 上一周期

        self.datatime = dt    # 周期的开始时间

    def onPrice(self, price):
        """更新周期的价格"""

        if price > self.high:
            self.high = price
            self.close = price
            return

        if price < self.low:
            self.low = price
            self.close = price
            return

        self.close = price

