# encoding: UTF-8

from __future__ import division

import os
import json
from eventEngine import Event
from eventType import *
from vtGateway import VtOrderReq, VtCancelOrderReq, VtOrderData
from vtConstant import *


path = os.path.abspath(os.path.dirname(__file__))


########################################################################
class HedgingEngine(object):
    """Delta对冲引擎"""
    SETTING_FILENAME = 'hedging_setting.json'
    SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)

    #----------------------------------------------------------------------
    def __init__(self, omEngine):
        """Constructor"""
        self.omEngine = omEngine
        self.eventEngine = omEngine.eventEngine
        self.mainEngine = omEngine.mainEngine
        
        self.inited = False
        self.portfolio = None
        
        self.underlyingSymbol = ''
        self.underlying = None
        
        self.targetDelta = 0
        self.deltaRange = 0
        self.deltaUpLimit = 0
        self.deltaDownLimit = 0
        
        self.hedgingActive = False
        self.hedgingCount = 0
        self.hedgingTrigger = 1
        
        self.tickAdd = 0            # 委托超价
        self.maxSpreadTick = 5      # 最大标的价差tick
        self.maxOrderSize = 20      # 最大单笔对冲手数
        
        self.activeOrderDict = {}
        
        self.loadSetting()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)
        
    #----------------------------------------------------------------------
    def init(self):
        """初始化对冲引擎"""
        self.portfolio = self.omEngine.portfolio
        
        # 获取对冲用标的物对象，如果没有指定则使用组合中标的物列表的第一个
        self.underlying = self.portfolio.underlyingDict.get(self.underlyingSymbol, None)
        if not self.underlying:
            self.underlying = self.portfolio.underlyingList[0]
        self.deltaRange = max(self.underlying.theoDelta, self.deltaRange)
        
        self.calculateDeltaLimit()
            
        self.inited = True
        
    #----------------------------------------------------------------------
    def setTargetDelta(self, targetDelta):
        """设置目标Delta"""
        self.targetDelta = targetDelta
        self.calculateDeltaLimit()
        
    #----------------------------------------------------------------------
    def setDeltaRange(self, deltaRange):
        """设置Delta范围限制"""
        # Delta对冲范围不能小于标的物的Delta数值一半，否则可能导致来回买卖
        deltaRange = max(int(self.underlying.theoDelta*0.5), deltaRange)
        self.deltaRange = deltaRange
        self.calculateDeltaLimit()
        
    #----------------------------------------------------------------------
    def setHedgingTrigger(self, hedgingTrigger):
        """设置对冲间隔"""
        self.hedgingTrigger = hedgingTrigger
        
    #----------------------------------------------------------------------
    def setTickAdd(self, tickAdd):
        """设置对冲时下单的超价"""
        self.tickAdd = tickAdd
        
    #----------------------------------------------------------------------
    def setMaxOrderSize(self, maxOrderSize):
        """"""
        self.maxOrderSize = maxOrderSize
        
    #----------------------------------------------------------------------
    def setMaxSpreadTick(self, maxSpreadTick):
        """"""
        self.maxSpreadTick = maxSpreadTick
        
    #----------------------------------------------------------------------
    def calculateDeltaLimit(self):
        """计算对冲上下限"""
        self.deltaDownLimit = self.targetDelta - self.deltaRange
        self.deltaUpLimit = self.targetDelta + self.deltaRange        
        
    #----------------------------------------------------------------------
    def start(self):
        """启动定时对冲"""
        if not self.inited:
            return
        
        self.hedgingActive = True
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止定时对冲"""
        self.hedgingActive = False
        
        self.cancelAll()
    
    #----------------------------------------------------------------------
    def resetUnderlying(self, symbol):
        """重设置标的物"""
        if symbol in self.portfolio.underlyingDict:
            self.underlyingSymbol = symbol
            self.underlying = self.portfolio.underlyingDict[symbol]

    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        pass
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """委托事件"""
        order = event.dict_['data']
        vtOrderID = order.vtOrderID
        
        # 状态为全成或撤销
        if (order.status is STATUS_ALLTRADED or
            order.status is STATUS_CANCELLED or
            order.status is STATUS_REJECTED):
            
            # 从活动委托字典中删除
            if vtOrderID in self.activeOrderDict:
                del self.activeOrderDict[vtOrderID]
                
        # 否则保存最新状态
        else:
            self.activeOrderDict[vtOrderID] = order
    
    #----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """定时事件"""
        if not self.hedgingActive:
            return
        
        # 每秒执行一次对之前未成交委托的全撤
        if self.activeOrderDict:
            self.cancelAll()
        
        self.hedgingCount += 1
        if self.hedgingCount >= self.hedgingTrigger:
            # 清空计数
            self.hedgingCount = 0
            
            # 若无活动委托则执行对冲
            if not self.activeOrderDict:
                self.hedgePortfolio()
        
        event = Event(EVENT_OM_HEDGING_STATUS)
        self.eventEngine.put(event)
            
    #----------------------------------------------------------------------
    def hedgePortfolio(self):
        """对冲整个组合的Delta到目标值"""
        posDelta = self.portfolio.posDelta
        underlying = self.underlying
        
        # 如果组合持仓Delta超过上下限
        if posDelta >= self.deltaUpLimit or posDelta <= self.deltaDownLimit:    
            # 计算对冲手数后取整
            hedgingVolume = (self.targetDelta - posDelta) / underlying.theoDelta
            hedgingVolume = int(round(hedgingVolume, 0))
            
            # 如果对冲标的买卖价差过宽，则不执行对冲
            if not underlying.askPrice1 or not underlying.bidPrice1:
                self.omEngine.writeLog(u'%s合约存在买卖价为0的情况，不执行对冲' %underlying.symbol)
                return
            
            if (underlying.askPrice1 - underlying.bidPrice1) > underlying.priceTick * self.maxSpreadTick:
                self.omEngine.writeLog(u'%s合约买卖价差过宽，不执行对冲' %underlying.symbol)
                return
            
            # 如果遭遇涨跌停，则立即停止运作
            if (underlying.bidPrice1 == underlying.upperLimit or 
                underlying.askPrice1 == underlying.lowerLimit):
                self.hedgingActive = False
                self.omEngine.writeLog(u'%s合约到达涨跌停板，已经停止自动对冲功能' %underlying.symbol)
                return
            
            # 如果数量非0则执行对冲操作
            if hedgingVolume:
                self.fastHedge(hedgingVolume)
        
    #----------------------------------------------------------------------
    def fastHedge(self, volume):
        """快速对冲"""
        underlying = self.underlying
        
        # 做多
        if volume > 0:
            price = underlying.askPrice1 + self.tickAdd * underlying.priceTick
            volume = min(abs(volume), self.maxOrderSize)                        # 对冲手数限制
            
            # 如果空头仓位大于等于买入量，则只需平
            if underlying.shortPos >= volume:
                self.fastTrade(DIRECTION_LONG, OFFSET_CLOSE, price, volume)
            # 否则先平后开
            else:
                openVolume = volume - underlying.shortPos
                if underlying.shortPos:
                    self.fastTrade(DIRECTION_LONG, OFFSET_CLOSE, price, underlying.shortPos)
                self.fastTrade(DIRECTION_LONG, OFFSET_OPEN, price, openVolume)
        # 做空
        else:
            price = underlying.bidPrice1 - self.tickAdd * underlying.priceTick
            volume = min(abs(volume), self.maxOrderSize)
            
            if underlying.longPos >= volume:
                self.fastTrade(DIRECTION_SHORT, OFFSET_CLOSE, price, volume)
            else:
                openVolume = volume - underlying.longPos
                if underlying.longPos:
                    self.fastTrade(DIRECTION_SHORT, OFFSET_CLOSE, price, underlying.longPos)
                self.fastTrade(DIRECTION_SHORT, OFFSET_OPEN, price, openVolume)
        
    #----------------------------------------------------------------------
    def fastTrade(self, direction, offset, price, volume):
        """封装下单函数"""
        underlying = self.underlying
        
        req = VtOrderReq()
        req.symbol = str(underlying.symbol)
        req.direction = direction
        req.offset = offset
        req.price = price
        req.volume = volume
        req.priceType = PRICETYPE_LIMITPRICE
        vtOrderID = self.omEngine.sendOrder(req, underlying.gatewayName)
        
        # 如果下单成功
        if vtOrderID:
            # 保存该委托到活动委托字典中
            order = VtOrderData()
            order.symbol = req.symbol
            order.orderID = vtOrderID.split('.')[1]
            order.gatewayName = underlying.gatewayName
            self.activeOrderDict[vtOrderID] = order         
            
            # 注册事件监听
            self.eventEngine.register(EVENT_ORDER + vtOrderID, self.processOrderEvent)
        
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelAll(self):
        """撤销之前的全部委托"""
        for vtOrderID, order in self.activeOrderDict.items():
            req = VtCancelOrderReq()
            req.symbol = order.symbol
            req.orderID = order.orderID
            self.mainEngine.cancelOrder(req, order.gatewayName)
            
        #self.activeOrderDict.clear()
    
    #----------------------------------------------------------------------
    def loadSetting(self):
        """载入配置"""
        f = file(self.SETTING_FILENAME, 'r')
        d = json.load(f)
        f.close()
        
        self.underlyingSymbol = d['underlyingSymbol']
        self.targetDelta = d['targetDelta']
        self.deltaRange = d['deltaRange']
        self.hedgingTrigger = d['hedgingTrigger']
        self.tickAdd = d['tickAdd']
        self.maxSpreadTick = d['maxSpreadTick']
        self.maxOrderSize = d['maxOrderSize']
        
    #----------------------------------------------------------------------
    def saveSetting(self):
        """保存配置"""
        f = file(self.SETTING_FILENAME, 'w')
        
        d = {
            'underlyingSymbol': self.underlyingSymbol,
            'targetDelta': self.targetDelta,
            'deltaRange': self.deltaRange,
            'hedgingTrigger': self.hedgingTrigger,
            'tickAdd': self.tickAdd,
            'maxSpreadTick': self.maxSpreadTick,
            'maxOrderSize': self.maxOrderSize
        }
        
        text = json.dumps(d, indent=4)
        f.write(text)
        f.close()
        
        
        
        
        
    
    