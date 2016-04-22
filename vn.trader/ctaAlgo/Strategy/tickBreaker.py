# encoding: UTF-8

import talib as ta
import numpy as np

from ctaBase import *
from ctaTemplate import CtaTemplate


########################################################################
class TickBreaker(CtaTemplate):
    """跳空追击策略(MC版本转化)"""

    className = 'TickBreaker'
    author = u'freeitaly'

    # 策略参数
    forward = 5      # 正向tick数量
    backward = 2     # 反向tick数量
    reForward = 1        # 再次转向tick数量
    maPeriod = 5      # 均线参数

    # 策略变量
    tickHistory = []       # 缓存tick报价的数组
    maxHistory = 10         # 最大缓存数量


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

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(TickBreaker, self).__init__(ctaEngine, setting)
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

        if tick.lastPrice != self.oldPrice:
            self.tickHistory.append(tick.lastPrice)

        # 检查列表长度，如果超过缓存上限则移除最老的数据
        # 这样是为了减少计算用的数据量，提高速度
        if len(self.tickHistory) > self.maxHistory:
            self.tickHistory.pop(0)
        # 如果小于缓存上限，则说明初始化数据尚未足够，不进行后续计算
        else:
            return

        # 将缓存的收盘价数转化为numpy数组后，传入talib的函数SMA中计算
        closeArray = np.array(self.closeHistory)
        sma = ta.SMA(closeArray, self.maPeriod)

        condition1 = 0      # >=5个上涨tick
        condition2 = 0      # 2个下跌tick
        condition3 = 0      # 1个上涨tick





        # 读取当前K线和上一根K线的数值，用于判断均线交叉
        self.fastMa0 = fastSMA[-1]
        self.fastMa1 = fastSMA[-2]
        self.slowMa0 = slowSMA[-1]
        self.slowMa1 = slowSMA[-2]

        # 判断买卖
        crossOver = self.fastMa0>self.slowMa0 and self.fastMa1<self.slowMa1     # 金叉上穿
        crossBelow = self.fastMa0<self.slowMa0 and self.fastMa1>self.slowMa1    # 死叉下穿

        # 金叉和死叉的条件是互斥
        if crossOver:
            # 如果金叉时手头没有持仓，则直接做多
            if self.pos == 0:
                self.buy(bar.close, 1)
            # 如果有空头持仓，则先平空，再做多
            elif self.pos < 0:
                self.cover(bar.close, 1)
                self.buy(bar.close, 1)
        # 死叉和金叉相反
        elif crossBelow:
            if self.pos == 0:
                self.short(bar.close, 1)
            elif self.pos > 0:
                self.sell(bar.close, 1)
                self.short(bar.close, 1)

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