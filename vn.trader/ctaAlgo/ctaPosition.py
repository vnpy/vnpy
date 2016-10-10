# encoding: UTF-8

from vtConstant import *
from ctaBase import *
import talib as ta

from datetime import datetime

DEBUGCTALOG = True

class CtaPosition:
    """策略的仓位管理类
    v 0.1 简单的数值，代表多仓数量和空仓数量

    """

    def __init__(self, strategy):
        self.strategy = strategy

        self.pos = 0        # 持仓状态 0:空仓 >=1 多仓 <=-1 空仓

        self.maxPos = 1        # 最大持仓量

        self.step = 1       # 增仓数量

        self.posList = []

        self.avgPrice = EMPTY_FLOAT

    def avaliablePos2Add(self):
        """剩余可加的仓位数量"""

        return self.maxPos - abs(self.pos)

    def openPos(self, direction, vol, price = EMPTY_FLOAT):
        """开、加仓"""

        if self.pos == 0:
            self.posList = []

        if direction == DIRECTION_LONG:     # 加多仓

            if self.pos + vol > self.maxPos:
                self.writeCtaLog(u'异常，超出仓位，当前仓位：{0},加仓:{1},最大仓位:{2}'.format(self.pos,vol,self.maxPos))
                return False

            self.writeCtaLog(u'仓位:{0}->{1}'.format(self.pos, self.pos+vol))
            self.pos = self.pos + vol
            self.strategy.pos = self.pos


        if direction == DIRECTION_SHORT:    # 加空仓

            if self.pos - vol < 0 - self.maxPos:
                self.writeCtaLog(u'异常，超出仓位，当前仓位：{0},加仓:{1},最大仓位:{2}'.format(self.pos, vol, self.maxPos))
                return False
            self.writeCtaLog(u'仓位:{0}->{1}'.format(self.pos, self.pos-vol))
            self.pos = self.pos - vol
            self.strategy.pos = self.pos

        if price > EMPTY_FLOAT:
                self.posList.append(price)

        # 计算持仓均价
        if len(self.posList) > 0:
                self.avgPrice = sum(self.posList)/len(self.posList)
                self.avgPrice = round(self.avgPrice, 3)

        return True

    def closePos(self, direction, vol):
        """平、减仓"""

        if direction == DIRECTION_LONG:     # 平空仓 Cover

            if self.pos + vol > 0:
                self.writeCtaLog(u'异常，超出仓位，当前仓位：{0},平仓:{1}'.format(self.pos,vol))
                self.strategy.pos = self.pos
                return False

            self.writeCtaLog(u'仓位:{0}->{1}'.format(self.pos, self.pos+vol))
            self.pos = self.pos + vol
            self.strategy.pos = self.pos

        if direction == DIRECTION_SHORT:    # 平多仓

            if self.pos - vol < 0 :
                self.writeCtaLog(u'异常，超出仓位，当前仓位：{0},加仓:{1}'.format(self.pos, vol))
                self.strategy.pos = self.pos
                return False

            self.writeCtaLog(u'仓位:{0}->{1}'.format(self.pos, self.pos-vol))
            self.pos = self.pos - vol
            self.strategy.pos = self.pos

        if abs(self.pos) > 0:
            self.posList = self.posList[:-vol]
        else:
            self.posList = []

        # 计算持仓均价
        if len(self.posList) > 0:
            self.avgPrice = sum(self.posList)/len(self.posList)
            self.avgPrice = round(self.avgPrice, 3)

        return True

    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        self.strategy.writeCtaLog(content)

    def debugCtaLog(self,content):
        """记录CTA日志"""
        if DEBUGCTALOG:
            self.strategy.writeCtaLog('[DEBUG]'+content)

