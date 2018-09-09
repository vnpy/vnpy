# encoding: UTF-8

from __future__ import division

from math import floor
from datetime import datetime

from vnpy.trader.vtConstant import (EMPTY_INT, EMPTY_FLOAT, 
                                    EMPTY_STRING, EMPTY_UNICODE)



EVENT_SPREADTRADING_TICK = 'eSpreadTradingTick.'
EVENT_SPREADTRADING_POS = 'eSpreadTradingPos.'
EVENT_SPREADTRADING_LOG = 'eSpreadTradingLog'
EVENT_SPREADTRADING_ALGO = 'eSpreadTradingAlgo.'
EVENT_SPREADTRADING_ALGOLOG = 'eSpreadTradingAlgoLog'



########################################################################
class StLeg(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING      # 代码
        self.ratio = EMPTY_INT          # 实际交易时的比例
        self.multiplier = EMPTY_FLOAT   # 计算价差时的乘数
        self.payup = EMPTY_INT          # 对冲时的超价tick
        
        self.bidPrice = EMPTY_FLOAT
        self.askPrice = EMPTY_FLOAT
        self.bidVolume = EMPTY_INT
        self.askVolume = EMPTY_INT
        
        self.longPos = EMPTY_INT
        self.shortPos = EMPTY_INT
        self.netPos = EMPTY_INT


########################################################################
class StSpread(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.name = EMPTY_UNICODE       # 名称
        self.symbol = EMPTY_STRING      # 代码（基于组成腿计算）
        
        self.activeLeg = None           # 主动腿
        self.passiveLegs = []           # 被动腿（支持多条）
        self.allLegs = []               # 所有腿
        
        self.bidPrice = EMPTY_FLOAT
        self.askPrice = EMPTY_FLOAT
        self.bidVolume = EMPTY_INT
        self.askVolume = EMPTY_INT
        self.time = EMPTY_STRING
        
        self.longPos = EMPTY_INT
        self.shortPos = EMPTY_INT
        self.netPos = EMPTY_INT
        
    #----------------------------------------------------------------------
    def initSpread(self):
        """初始化价差"""
        # 价差最少要有一条主动腿
        if not self.activeLeg:
            return
        
        # 生成所有腿列表
        self.allLegs.append(self.activeLeg)
        self.allLegs.extend(self.passiveLegs)
        
        # 生成价差代码
        legSymbolList = []
        
        for leg in self.allLegs:
            if leg.multiplier >= 0:
                legSymbol = '+%s*%s' %(leg.multiplier, leg.vtSymbol)
            else:
                legSymbol = '%s*%s' %(leg.multiplier, leg.vtSymbol)
            legSymbolList.append(legSymbol)
        
        self.symbol = ''.join(legSymbolList)
        
    #----------------------------------------------------------------------
    def calculatePrice(self):
        """计算价格"""
        # 清空价格和委托量数据
        self.bidPrice = EMPTY_FLOAT
        self.askPrice = EMPTY_FLOAT
        self.askVolume = EMPTY_INT
        self.bidVolume = EMPTY_INT
        
        # 遍历价差腿列表
        for n, leg in enumerate(self.allLegs):
            # 过滤有某条腿尚未初始化的情况（无挂单量）
            if not leg.bidVolume or not leg.askVolume:
                self.bidPrice = EMPTY_FLOAT
                self.askPrice = EMPTY_FLOAT
                self.askVolume = EMPTY_INT
                self.bidVolume = EMPTY_INT                
                return
                
            # 计算价格
            if leg.multiplier > 0:
                self.bidPrice += leg.bidPrice * leg.multiplier
                self.askPrice += leg.askPrice * leg.multiplier
            else:
                self.bidPrice += leg.askPrice * leg.multiplier
                self.askPrice += leg.bidPrice * leg.multiplier
                
            # 计算报单量
            if leg.ratio > 0:
                legAdjustedBidVolume = floor(leg.bidVolume / leg.ratio)
                legAdjustedAskVolume = floor(leg.askVolume / leg.ratio)
            else:
                legAdjustedBidVolume = floor(leg.askVolume / abs(leg.ratio))
                legAdjustedAskVolume = floor(leg.bidVolume / abs(leg.ratio))
            
            if n == 0:
                self.bidVolume = legAdjustedBidVolume                           # 对于第一条腿，直接初始化
                self.askVolume = legAdjustedAskVolume
            else:
                self.bidVolume = min(self.bidVolume, legAdjustedBidVolume)      # 对于后续的腿，价差可交易报单量取较小值
                self.askVolume = min(self.askVolume, legAdjustedAskVolume)
                
        # 更新时间
        self.time = datetime.now().strftime('%H:%M:%S.%f')[:-3]
        
    #----------------------------------------------------------------------
    def calculatePos(self):
        """计算持仓"""
        # 清空持仓数据
        self.longPos = EMPTY_INT
        self.shortPos = EMPTY_INT
        self.netPos = EMPTY_INT
        
        # 遍历价差腿列表
        for n, leg in enumerate(self.allLegs):
            if leg.ratio > 0:
                legAdjustedLongPos = floor(leg.longPos / leg.ratio)
                legAdjustedShortPos = floor(leg.shortPos / leg.ratio)
            else:
                legAdjustedLongPos = floor(leg.shortPos / abs(leg.ratio))
                legAdjustedShortPos = floor(leg.longPos / abs(leg.ratio))
            
            if n == 0:
                self.longPos = legAdjustedLongPos
                self.shortPos = legAdjustedShortPos
            else:
                self.longPos = min(self.longPos, legAdjustedLongPos)
                self.shortPos = min(self.shortPos, legAdjustedShortPos)
        
        # 计算净仓位
        self.longPos = int(self.longPos)
        self.shortPos = int(self.shortPos)
        self.netPos = self.longPos - self.shortPos
    
    #----------------------------------------------------------------------
    def addActiveLeg(self, leg):
        """添加主动腿"""
        self.activeLeg = leg
    
    #----------------------------------------------------------------------
    def addPassiveLeg(self, leg):
        """添加被动腿"""
        self.passiveLegs.append(leg)
        
        
    
    