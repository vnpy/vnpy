# encoding: UTF-8

from vtConstant import *
from ctaBase import *
import talib as ta

from datetime import datetime

DEBUGCTALOG = True

class CtaPosition:
    """策略的仓位管理类
    v 0.1 简单的数值，代表多仓数量和空仓数量
    v 0.2 增加多仓和空仓的持仓，去除持仓均价
    """

    def __init__(self, strategy):
        self.strategy = strategy
        self.longPos = 0    # 多仓持仓
        self.shortPos = 0   # 空仓持仓
        self.pos = 0        # 持仓状态 0:空仓/对空平等； >=1 净多仓 ；<=-1 净空仓
        self.maxPos = 1        # 最大持仓量（多仓+空仓总量）
        self.step = 1       # 增仓数量

        # disabled in v0.2
        #self.posList = []
        #self.avgPrice = EMPTY_FLOAT

    def avaliablePos2Add(self):
        """剩余可加的仓位数量"""
        return self.maxPos - abs(self.longPos) - abs(self.shortPos)

    def openPos(self, direction, vol, price=EMPTY_FLOAT):
        """开、加仓"""
        # vol: 正整数

        # disabled in v0.2
        #if self.pos == 0:
        #    self.posList = []

        if direction == DIRECTION_LONG:     # 加多仓
            if (max(self.pos, self.longPos) + vol) > self.maxPos:
                self.writeCtaError(u'异常，超出仓位。净:{0},多:{1},加多:{2},最大:{3}'
                                 .format(self.pos, self.longPos, vol, self.maxPos))

                # 只告警
                #return False

            # 更新
            self.writeCtaLog(u'多仓:{0}->{1}'.format(self.longPos, self.longPos + vol))
            self.writeCtaLog(u'净:{0}->{1}'.format(self.pos, self.pos + vol))
            self.longPos += vol
            self.pos += vol

            # 更新上层策略的pos。该方法不推荐使用
            self.strategy.pos = self.pos

        if direction == DIRECTION_SHORT:    # 加空仓
            if (min(self.pos, self.shortPos) - vol) < (0 - self.maxPos):
                self.writeCtaError(u'异常，超出仓位。净:{0},空:{1},加空:{2},最大:{3}'
                                 .format(self.pos, self.shortPos, vol, self.maxPos))
                #return False

            self.writeCtaLog(u'空仓:{0}->{1}'.format(self.shortPos, self.shortPos - vol))
            self.writeCtaLog(u'净:{0}->{1}'.format(self.pos, self.pos-vol))
            self.shortPos -= vol
            self.pos -= vol

            # 更新上层策略的pos。该方法不推荐使用
            self.strategy.pos = self.pos

        # v0.2 disabled
        #if price > EMPTY_FLOAT:
        #        self.posList.append(price)

        # 计算持仓均价
        #if len(self.posList) > 0:
        #        self.avgPrice = sum(self.posList)/len(self.posList)
        #        self.avgPrice = round(self.avgPrice, 3)

        return True

    def closePos(self, direction, vol):
        """平、减仓"""
        # vol: 正整数

        if direction == DIRECTION_LONG:     # 平空仓 Cover
            if self.shortPos + vol > 0:
                self.writeCtaError(u'异常，超出仓位。净:{0},空:{1},平仓:{2}'.format(self.pos, self.shortPos, vol))
                #self.strategy.pos = self.pos
                #return False

            self.writeCtaLog(u'空仓:{0}->{1}'.format(self.shortPos, self.shortPos + vol))
            self.writeCtaLog(u'净:{0}->{1}'.format(self.pos, self.pos + vol))
            self.shortPos += vol
            self.pos += vol

            # 更新上层策略的pos。该方法不推荐使用
            self.strategy.pos = self.pos

        if direction == DIRECTION_SHORT:    # 平多仓
            if self.longPos - vol < 0:
                self.writeCtaError(u'异常，超出仓位。净:{0},多:{1},平仓:{2}'.format(self.pos, self.longPos, vol))
                #self.strategy.pos = self.pos
                #return False

            self.writeCtaLog(u'多仓:{0}->{1}'.format(self.longPos, self.longPos - vol))
            self.writeCtaLog(u'净:{0}->{1}'.format(self.pos, self.pos-vol))

            self.shortPos -= vol
            self.pos -= vol
            self.strategy.pos = self.pos

        # disabled in v0.2
        #if abs(self.pos) > 0:
        #    self.posList = self.posList[:-vol]
        #else:
        #    self.posList = []

        # 计算持仓均价
        #if len(self.posList) > 0:
        #    self.avgPrice = sum(self.posList)/len(self.posList)
        #    self.avgPrice = round(self.avgPrice, 3)

        return True

    def clear(self):
        """清除状态"""
        self.writeCtaLog(u'清除所有持仓状态')
        self.pos = 0
        self.longPos = 0
        self.shortPos = 0
        # 更新上层策略的pos
        self.strategy.pos = 0

    # ----------------------------------------------------------------------
    def writeCtaError(self, content):
        """记录CTA日志错误"""
        self.strategy.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        self.strategy.writeCtaLog(content)

    def debugCtaLog(self, content):
        """记录CTA日志"""
        if DEBUGCTALOG:
            self.strategy.writeCtaLog('[DEBUG]'+content)

