# encoding: UTF-8

import talib as ta
import numpy as np

from ctaBase import *
from ctaTemplate import CtaTemplate

import time
########################################################################
class TickBreaker(CtaTemplate):
    """跳空追击策略(MC版本转化)"""

    className = 'TickBreaker'
    author = u'融拓科技'

    # 策略参数
    forward = 5      # 正向tick数量
    backward = 2     # 反向tick数量
    reForward = 1        # 再次转向tick数量
    maPeriod = 5      # 均线参数

    # 策略变量
    tickHistory = []       # 缓存tick报价的数组
    maxHistory = 7         # 最大缓存数量

    forwardNo = EMPTY_INT     # 正向tick数量
    backwardNo = EMPTY_INT     # 反向tick数量
    reForwardNo = EMPTY_INT        # 再次转向tick数量



    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'forward',
                 'backward',
                 'reForward'
                 ]

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'forwardNo',
               'backwardNo',
               'reForwardNo'
               ]

    # condition1 = False      # >=5个上涨tick
    # condition2 = False      # 2个下跌tick
    # condition3 = False      # 1个上涨tick

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(TickBreaker, self).__init__(ctaEngine, setting)
        # 注意策略类中的可变对象属性（通常是list和dict等），在策略初始化时需要重新创建，
        # 否则会出现多个策略实例之间数据共享的情况，有可能导致潜在的策略逻辑错误风险，
        # 策略类中的这些可变对象属性可以选择不写，全都放在__init__下面，写主要是为了阅读
        # 策略时方便（更多是个编程习惯的选择）

        # 策略变量
        self.tickHistory = []       # 缓存tick报价的数组
        self.maxHistory = 7         # 最大缓存数量

        self.forwardNo = EMPTY_INT     # 正向tick数量
        self.backwardNo = EMPTY_INT     # 反向tick数量
        self.reForwardNo = EMPTY_INT        # 再次转向tick数量

        self.oldPrice = 0       # 上一个tick的lastPrice

    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'tick策略初始化')

        self.putEvent()

    # ----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'tick策略启动')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'tick策略停止')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        # 把最新的收盘价缓存到列表中
        start = time.time()
        if tick.lastPrice != self.oldPrice:
            self.tickHistory.append(tick.lastPrice)
            self.oldPrice = tick.lastPrice
        else:
            return
        # 检查列表长度，如果超过缓存上限则移除最老的数据
        # 这样是为了减少计算用的数据量，提高速度
        if len(self.tickHistory) > self.maxHistory:
            self.tickHistory.pop(0)
        # 如果小于缓存上限，则说明初始化数据尚未足够，不进行后续计算
        else:
            return

        # # 将缓存的收盘价数转化为numpy数组后，传入talib的函数SMA中计算
        # closeArray = np.array(self.closeHistory)
        # sma = ta.SMA(closeArray, self.maPeriod)

        # # >=5个上涨tick
        # condition1 = self.tickHistory[0] < self.tickHistory[1] < self.tickHistory[2] < self.tickHistory[3] < self.tickHistory[4]
        # # 2个下跌tick
        # condition2 = self.tickHistory[4] > self.tickHistory[5] > self.tickHistory[6]
        # # 1个上涨tick
        # condition3 = self.tickHistory[6] < self.tickHistory[7]
        # print self.tickHistory
        # print 'buy:    ', int(condition1), '   ', int(condition2), '   ', int(condition3)
        # buyCondition = condition1 and condition2 and condition3
        #
        # # >=5个下跌tick
        # condition1 = self.tickHistory[0] > self.tickHistory[1] > self.tickHistory[2] > self.tickHistory[3] > self.tickHistory[4]
        # # 2个上涨tick
        # condition2 = self.tickHistory[4] < self.tickHistory[5] < self.tickHistory[6]
        # # 1个下跌tick
        # condition3 = self.tickHistory[6] > self.tickHistory[7]
        # print 'sell:    ', int(condition1), '   ', int(condition2), '   ', int(condition3)
        #
        # sellCondition = condition1 and condition2 and condition3

        # >=5个上涨tick
        condition1 = self.tickHistory[0] < self.tickHistory[1] < self.tickHistory[2] < self.tickHistory[3]
        # 2个下跌tick
        condition2 = self.tickHistory[3] > self.tickHistory[4] > self.tickHistory[5]
        # 1个上涨tick
        condition3 = self.tickHistory[5] < self.tickHistory[6]
        # print self.tickHistory
        # print 'buy:    ', int(condition1), '   ', int(condition2), '   ', int(condition3)
        buyCondition = condition1 and condition2 and condition3

        # >=5个下跌tick
        condition1 = self.tickHistory[0] > self.tickHistory[1] > self.tickHistory[2] > self.tickHistory[3]
        # 2个上涨tick
        condition2 = self.tickHistory[3] < self.tickHistory[4] < self.tickHistory[5]
        # 1个下跌tick
        condition3 = self.tickHistory[5] > self.tickHistory[6]
        # print 'sell:    ', int(condition1), '   ', int(condition2), '   ', int(condition3)

        sellShortCondition = condition1 and condition2 and condition3
        # 金叉和死叉的条件是互斥
        if buyCondition:
            # 如果金叉时手头没有持仓，则直接做多
            if self.pos == 0:
                self.buy(tick.lastPrice, 1)
            # 如果有空头持仓，则先平空，再做多
            elif self.pos < 0:
                self.cover(tick.lastPrice, 1)
                self.buy(tick.lastPrice, 1)
        # 死叉和金叉相反
        elif sellShortCondition:
            if self.pos == 0:
                self.short(tick.lastPrice, 1)
            elif self.pos > 0:
                self.sell(tick.lastPrice, 1)
                self.short(tick.lastPrice, 1)

        sellCondition = self.tickHistory[4] > self.tickHistory[5] > self.tickHistory[6]
        buyCoverCondition = self.tickHistory[4] < self.tickHistory[5] < self.tickHistory[6]

        # if self.pos > 0 and sellCondition:
        #     self.sell(tick.lastPrice, 1)
        #
        # if self.pos < 0 and buyCoverCondition:
        #     self.cover(tick.lastPrice, 1)

        # print time.time() - start

        # 发出状态更新事件
        self.putEvent()

    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        pass
    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass