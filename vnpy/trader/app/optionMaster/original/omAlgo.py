# encoding: UTF-8

from __future__ import division

import json
import os
import traceback

from eventType import *
from eventEngine import Event
from vtConstant import *
from vtGateway import VtOrderData, VtOrderReq, VtCancelOrderReq
from omPricing import calculatePrice

path = os.path.abspath(os.path.dirname(__file__))


########################################################################
class AlgoEngine(object):
    """算法引擎"""
    SETTING_FILENAME = 'algo_setting.json'
    SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)

    #----------------------------------------------------------------------
    def __init__(self, omEngine):
        """Constructor"""
        self.omEngine = omEngine
        self.riskEngine = omEngine.riskEngine
        self.eventEngine = omEngine.eventEngine
        self.mainEngine = omEngine.mainEngine
        
        self.portfolio = None
        self.algoDict = {}      # 算法字典
    
    #----------------------------------------------------------------------
    def init(self):
        """初始化引擎"""
        self.portfolio = self.omEngine.portfolio
        
        for chain in self.portfolio.chainList:
            for option in chain.optionList:
                algo = MmEeAlgo(option, self)
                self.algoDict[algo.symbol] = algo
                
        self.loadSetting()
    
    #----------------------------------------------------------------------
    def startAllPricing(self):
        """启动全部定价"""
        for algo in self.algoDict.values():
            algo.startPricing()
    
    #----------------------------------------------------------------------
    def startAllTrading(self):
        """启动全部交易"""
        for algo in self.algoDict.values():
            algo.startTrading()
    
    #----------------------------------------------------------------------
    def stopAllPricing(self):
        """停止全部定价"""
        for algo in self.algoDict.values():
            algo.stopPricing()
    
    #----------------------------------------------------------------------
    def stopAllTrading(self):
        """停止全部交易"""
        for algo in self.algoDict.values():
            algo.stopTrading()
    
    #----------------------------------------------------------------------
    def saveSetting(self):
        """保存配置"""
        d = {}
        for symbol, algo in self.algoDict.items():
            d[symbol] = algo.getSetting()
        
        text = json.dumps(d, indent=4)

        with open(self.SETTING_FILENAME, 'w') as f:
            f.write(text)

    #----------------------------------------------------------------------
    def loadSetting(self):
        """加载配置"""
        try:
            f = file(self.SETTING_FILENAME, 'r')
            d = json.load(f)
            
            for symbol, setting in d.items():
                if symbol in self.algoDict:
                    self.algoDict[symbol].init(setting)
        except:
            msg = traceback.format_exc()
            self.omEngine.writeLog(msg)


########################################################################
class AlgoTemplate(object):
    """算法模板"""

    #----------------------------------------------------------------------
    def __init__(self, option, algoEngine):
        """Constructor"""
        self.option = option
        self.underlying = option.underlying
        self.symbol = option.symbol
        
        self.algoEngine = algoEngine
        self.omEngine = algoEngine.omEngine
        self.riskEngine = algoEngine.riskEngine
        self.eventEngine = algoEngine.eventEngine
        self.mainEngine = algoEngine.mainEngine
        
        self.pricingActive = False      # 定价状态
        self.tradingActive = False      # 交易状态
        
        self.longOrderDict = {}         # 多头委托字典
        self.shortOrderDict = {}        # 空头委托字典
    
    #----------------------------------------------------------------------
    def init(self, setting):
        """初始化"""
        pass        
    
    #----------------------------------------------------------------------
    def getSetting(self):
        """返回配置信息"""
        pass
    
    #----------------------------------------------------------------------
    def startPricing(self):
        """启动定价"""
        pass
    
    #----------------------------------------------------------------------
    def stopPricing(self):
        """停止定价"""
        pass
    
    #----------------------------------------------------------------------
    def startTrading(self):
        """启动交易"""
        pass
    
    #----------------------------------------------------------------------
    def stopTrading(self):
        """停止交易"""
        pass
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        pass
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """处理行情事件"""
        pass
    
    #----------------------------------------------------------------------
    def processUnderlyingTickEvent(self, event):
        """处理标的行情事件"""
        pass
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """处理成交事件"""
        pass
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """处理委托事件"""
        pass
    
    #----------------------------------------------------------------------
    def cancelAll(self):
        """全撤"""
        pass


########################################################################
class MmEeAlgo(AlgoTemplate):
    """"""
    LONG_ONLY = u'只多'
    SHORT_ONLY = u'只空'
    LONG_SHORT = u'双向'

    #----------------------------------------------------------------------
    def __init__(self, option, algoEngine):
        """Constructor"""
        super(MmEeAlgo, self).__init__(option, algoEngine)
        
        # 参数
        self.priceSpread = 0
        self.impvSpread = 0
        
        self.posTarget = 0
        self.posRange = 0
        self.orderSizeLimit = 0
        
        self.tradingDirection = self.LONG_SHORT
        
        # 变量
        self.algoSpread = 0
        self.algoImpv = 0
        self.algoMid = 0
        self.algoBidLimit = 0
        self.algoAskLimit = 0
        
        self.algoBidPrice = 0
        self.algoBidVolume = 0
        self.algoAskPrice = 0
        self.algoAskVolume = 0
        
        self.posUpLimit = 0
        self.posDownLimit = 0
        
        self.strike = option.strike
        self.optionType = option.optionType
        self.expiryTime = option.expiryTime
        
        self.cancelTimes = self.riskEngine.getCancelTimes(self.symbol)
        
    #----------------------------------------------------------------------
    def startPricing(self):
        """启动定价"""
        if self.pricingActive:
            return
        
        if self.priceSpread or self.impvSpread:
            self.pricingActive = True
            
            self.calculateAlgoMid()
            self.calculateAlgoSpread()
            self.calculateAlgoBidAsk()
            self.putEvent(EVENT_OM_ALGO_CONTROL)
    
    #----------------------------------------------------------------------
    def stopPricing(self):
        """停止定价"""
        if not self.pricingActive:
            return
        
        if not self.tradingActive:
            self.pricingActive = False
            
            self.algoSpread = 0
            self.algoImpv = 0
            self.algoMid = 0
            self.algoBidLimit = 0
            self.algoAskLimit = 0
            self.putEvent(EVENT_OM_ALGO_CONTROL)
    
    #----------------------------------------------------------------------
    def startTrading(self):
        """启动交易"""
        if self.tradingActive:
            return
        
        if self.pricingActive and (self.posRange or self.posTarget) and self.orderSizeLimit:
            self.tradingActive = True
            self.putEvent(EVENT_OM_ALGO_CONTROL)
    
    #----------------------------------------------------------------------
    def stopTrading(self):
        """停止交易"""
        if not self.tradingActive:
            return
        
        # 停止算法
        self.tradingActive = False
        self.cancelAll()    
        
        # 清空状态
        self.longOrderDict.clear()
        self.shortOrderDict.clear()
        
        self.algoBidPrice = 0
        self.algoBidVolume = 0
        self.algoAskPrice = 0
        self.algoAskVolume = 0
        
        # 发出通知
        self.putEvent(EVENT_OM_ALGO_CONTROL)
        
    #----------------------------------------------------------------------
    def init(self, setting):
        """初始化"""
        if setting:
            self.priceSpread = setting['priceSpread']
            self.impvSpread = setting['impvSpread']
            self.posTarget = setting['posTarget']
            self.posRange = setting['posRange']
            self.orderSizeLimit = setting['orderSizeLimit']
            self.tradingDirection = setting['tradingDirection']
        
        self.calculatePosLimit()
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def calculatePosLimit(self):
        """计算仓位限制"""
        self.posUpLimit = self.posTarget + self.posRange
        self.posDownLimit = self.posTarget - self.posRange
    
    #----------------------------------------------------------------------
    def getSetting(self):
        """返回配置"""
        d = {
            'priceSpread': self.priceSpread,
            'impvSpread': self.impvSpread,
            'posTarget': self.posTarget,
            'posRange': self.posRange,
            'orderSizeLimit': self.orderSizeLimit,
            'tradingDirection': self.tradingDirection
        }
        
        return d
        
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情事件"""
        if self.pricingActive:
            self.calculateAlgoSpread()
            self.calculateAlgoBidAsk()
            self.cancelTimes = self.riskEngine.getCancelTimes(self.symbol)
            self.putEvent(EVENT_OM_ALGO_PRICING)
            
        if self.tradingActive:
            self.quote()
            self.putEvent(EVENT_OM_ALGO_TRADING)
    
    #----------------------------------------------------------------------
    def processUnderlyingTickEvent(self, event):
        """标的行情事件"""
        if self.pricingActive:
            self.calculateAlgoMid()
            self.calculateAlgoBidAsk()
            self.cancelTimes = self.riskEngine.getCancelTimes(self.symbol)
            self.putEvent(EVENT_OM_ALGO_PRICING)
        
        if self.tradingActive:  
            self.quote()
            self.putEvent(EVENT_OM_ALGO_TRADING)
            
        # 非交易状态，则检查是否还有活动委托要撤
        else:
            if self.longOrderDict:
                self.cancelAllLong()
                
            if self.shortOrderDict:
                self.cancelAllShort()
            
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        trade = event.dict_['data']
        
        if trade.direction is DIRECTION_LONG:
            self.algoBidVolume = max(self.algoBidVolume - trade.volume, 0)
        else:
            self.algoAskVolume = max(self.algoAskVolume - trade.volume, 0)
            
        self.putEvent(EVENT_OM_ALGO_TRADING)
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """处理委托事件"""
        order = event.dict_['data']
        vtOrderID = order.vtOrderID
        
        # 状态为全成或撤销
        if (order.status is STATUS_ALLTRADED or
            order.status is STATUS_CANCELLED or
            order.status is STATUS_REJECTED):
            
            # 从活动委托字典中删除
            if vtOrderID in self.longOrderDict:
                del self.longOrderDict[vtOrderID]
            elif vtOrderID in self.shortOrderDict:
                del self.shortOrderDict[vtOrderID]
                
        # 否则保存最新状态
        else:
            if vtOrderID in self.longOrderDict:
                self.longOrderDict[vtOrderID] = order   
            elif vtOrderID in self.shortOrderDict:
                self.shortOrderDict[vtOrderID] = order

    #----------------------------------------------------------------------
    def calculateAlgoMid(self):
        """计算中间价"""
        priceTick = self.option.priceTick
        self.algoImpv = self.option.pricingImpv
        self.algoMid = self.option.theoPrice
        self.algoMid = round(self.algoMid/priceTick, 0) * priceTick
        
    #----------------------------------------------------------------------
    def calculateAlgoSpread(self):
        """计算价差"""
        impvPriceSpread = self.impvSpread * self.option.theoVega / self.option.size
        self.algoSpread = max(self.priceSpread, impvPriceSpread)
        
    #----------------------------------------------------------------------
    def calculateAlgoBidAsk(self):
        """计算买卖价"""
        halfSpread = self.algoSpread / 2
        priceTick = self.option.priceTick
        
        # 计算买卖价上限
        self.algoAskLimit = self.algoMid + halfSpread
        self.algoBidLimit = self.algoMid - halfSpread
        
        # 取整到priceTick
        self.algoAskLimit = round(self.algoAskLimit/priceTick, 0) * priceTick
        self.algoBidLimit = round(self.algoBidLimit/priceTick, 0) * priceTick
        
    #----------------------------------------------------------------------
    def quote(self):
        """执行交易"""
        if self.tradingDirection == self.LONG_SHORT:
            self.quoteLong()
            self.quoteShort()
        elif self.tradingDirection == self.LONG_ONLY:
            self.quoteLong()
        else:
            self.quoteShort()
        
    #----------------------------------------------------------------------
    def quoteLong(self):
        """多头交易"""
        option = self.option
        
        # 如果缺少期权价格或者无算法定价，不交易
        if not option.bidPrice1 or not self.algoMid:
            return

        # 检查持仓情况，超过则不交易
        if option.netPos >= self.posUpLimit:
            if self.longOrderDict:
                self.cancelAllLong()
            return
                
        # 检查价格是否超过上限，超过则不交易
        if option.bidPrice1 > self.algoBidLimit:
            if self.longOrderDict:
                self.cancelAllLong()
            return
        
        # 检查是否是最优报价，若是则无需操作
        if option.bidPrice1 == self.algoBidPrice and self.longOrderDict:
            return
        
        # 否则，都需要重新报价
        else:
            # 如果还有活动委托则必须先撤
            if self.longOrderDict:
                self.cancelAllLong()
            # 否则直接下单
            else:
                volume = min(self.posUpLimit-option.netPos, self.orderSizeLimit)
                price = option.bidPrice1 + option.priceTick
                self.fastLong(price, volume)
     
    #----------------------------------------------------------------------
    def quoteShort(self):
        """空头交易"""
        option = self.option
        
        if not option.askPrice1 or not self.algoMid:
            return
        
        if option.netPos <= self.posDownLimit:
            if self.shortOrderDict:
                self.cancelAllShort()
            return
        
        if option.askPrice1 < self.algoAskLimit:
            if self.shortOrderDict:
                self.cancelAllLong()
            return
        
        if option.askPrice1 == self.algoAskPrice and self.shortOrderDict:
            return
        
        else:
            if self.shortOrderDict:
                self.cancelAllShort()
            else:
                volume = min(abs(self.posDownLimit-option.netPos), self.orderSizeLimit)
                price = option.askPrice1 - option.priceTick
                self.fastShort(price, volume)
    
    #----------------------------------------------------------------------
    def cancelOrders(self, d):
        """撤字典中所有的委托"""
        for orderID, order in d.items():
            req = VtCancelOrderReq()
            req.symbol = order.symbol
            req.orderID = order.orderID
            self.mainEngine.cancelOrder(req, order.gatewayName)
            
    #----------------------------------------------------------------------
    def cancelAllLong(self):
        """多头全撤"""
        if self.longOrderDict:
            self.cancelOrders(self.longOrderDict)
        self.algoBidPrice = 0
        self.algoBidVolume = 0
        
    #----------------------------------------------------------------------
    def cancelAllShort(self):
        """空头全撤"""
        if self.shortOrderDict:
            self.cancelOrders(self.shortOrderDict)
        self.algoAskPrice = 0
        self.algoAskVolume = 0
    
    #----------------------------------------------------------------------
    def cancelAll(self):
        """全部撤单"""
        self.cancelAllLong()
        self.cancelAllShort()
        
    #----------------------------------------------------------------------
    def fastLong(self, price, volume):
        """快速做多"""        
        option = self.option
        
        if option.shortPos >= volume:
            self.fastTrade(DIRECTION_LONG, OFFSET_CLOSE, price, volume)
        else:
            openVolume = volume - option.shortPos
            if option.shortPos:
                self.fastTrade(DIRECTION_LONG, OFFSET_CLOSE, price, option.shortPos)
            self.fastTrade(DIRECTION_LONG, OFFSET_OPEN, price, openVolume)
            
        self.algoBidPrice = price
        self.algoBidVolume = volume
    
    #----------------------------------------------------------------------
    def fastShort(self, price, volume):
        """快速做空"""
        option = self.option
        
        if option.longPos >= volume:
            self.fastTrade(DIRECTION_SHORT, OFFSET_CLOSE, price, volume)
        else:
            openVolume = volume - option.longPos
            if option.longPos:
                self.fastTrade(DIRECTION_SHORT, OFFSET_CLOSE, price, option.longPos)
            self.fastTrade(DIRECTION_SHORT, OFFSET_OPEN, price, openVolume)
        
        self.algoAskPrice = price
        self.algoAskVolume = volume
        
    #----------------------------------------------------------------------
    def fastTrade(self, direction, offset, price, volume):
        """封装下单函数"""
        option = self.option
        
        req = VtOrderReq()
        req.symbol = str(option.symbol)
        req.direction = direction
        req.offset = offset
        req.price = price
        req.volume = volume
        req.priceType = PRICETYPE_LIMITPRICE
        vtOrderID = self.omEngine.sendOrder(req, option.gatewayName)
        
        # 如果下单成功
        if vtOrderID:
            # 保存该委托到活动委托字典中
            order = VtOrderData()
            order.symbol = req.symbol
            order.orderID = vtOrderID.split('.')[1]
            order.vtOrderID = vtOrderID
            order.gatewayName = option.gatewayName
            
            if direction is DIRECTION_LONG:
                self.longOrderDict[vtOrderID] = order
            else:
                self.shortOrderDict[vtOrderID] = order
            
            # 注册事件监听
            self.eventEngine.register(EVENT_ORDER + vtOrderID, self.processOrderEvent)
        
        return vtOrderID    
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        vtSymbol = self.option.vtSymbol
        underlyingVtSymbol = self.underlying.vtSymbol
        
        self.eventEngine.register(EVENT_TICK + underlyingVtSymbol, self.processUnderlyingTickEvent)
        self.eventEngine.register(EVENT_TICK + vtSymbol, self.processTickEvent)
        self.eventEngine.register(EVENT_TRADE + vtSymbol, self.processTradeEvent)    
    
    #----------------------------------------------------------------------
    def setPriceSpread(self, priceSpread):
        """设置价差"""
        self.priceSpread = priceSpread
        self.calculateAlgoSpread()
        
    #----------------------------------------------------------------------
    def setImpvSpread(self, impvSpread):
        """设置波动率价差"""
        self.impvSpread = impvSpread
        self.calculateAlgoSpread()
        
    #----------------------------------------------------------------------
    def setPosTarget(self, posTarget):
        """设置目标持仓"""
        self.posTarget = posTarget
        self.calculatePosLimit()
        
    #----------------------------------------------------------------------
    def setPosRange(self, posRange):
        """设置持仓范围"""
        self.posRange = posRange
        self.calculatePosLimit()
        
    #----------------------------------------------------------------------
    def setOrderSizeLimit(self, orderSizeLimit):
        """设置委托大小限制"""
        self.orderSizeLimit = orderSizeLimit
        
    #----------------------------------------------------------------------
    def setTradingDirection(self, tradingDirection):
        """设置交易方向"""
        self.tradingDirection = tradingDirection
    
    #----------------------------------------------------------------------
    def putEvent(self, type_):
        """发出事件"""
        event = Event(type_)
        event.dict_['data'] = self.symbol
        self.eventEngine.put(event)