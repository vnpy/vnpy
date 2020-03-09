# encoding: UTF-8

# 周期类，定义CTA的五种周期，及其周期变换矩阵
from enum import Enum
from datetime import datetime


# 周期方向
class Period(Enum):
    INIT = u'初始状态'
    LONG = u'多'
    SHORT = u'空'
    SHOCK = u'震荡'
    LONG_EXTREME = u'极端多'
    SHORT_EXTREME = u'极端空'


class CtaPeriod(object):
    """CTA 周期"""

    def __init__(self, mode: Period, price: float, pre_mode: Period = Period.INIT, dt: datetime = None):
        """初始化函数"""
        self.open = price  # 开始价格
        self.close = price  # 结束价格
        self.high = price  # 最高价格
        self.low = price  # 最低价格

        self.mode = mode  # 周期模式 XXX
        self.pre_mode = pre_mode  # 上一周期

        self.datetime = dt if dt else datetime.now()  # 周期的开始时间

    def update_price(self, price):
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
