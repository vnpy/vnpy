# encoding: UTF-8

from __future__ import division
from datetime import datetime

from vnpy.trader.vtConstant import STATUS_NOTTRADED, STATUS_PARTTRADED, STATUS_UNKNOWN


# 活动委托状态
STATUS_ACTIVE = [STATUS_NOTTRADED, STATUS_PARTTRADED, STATUS_UNKNOWN]


########################################################################
class AlgoTemplate(object):
    """算法模板"""
    templateName = 'AlgoTemplate'
    
    timestamp = ''
    count = 0
    
    @classmethod
    #----------------------------------------------------------------------
    def new(cls, engine, setting):
        """创建新对象"""
        timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
        if timestamp != cls.timestamp:
            cls.timestamp = timestamp
            cls.count = 0
        else:
            cls.count += 1
            
        algoName = '_'.join([cls.templateName, cls.timestamp, str(cls.count)])
        algo = cls(engine, setting, algoName)
        return algo

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        self.engine = engine
        self.active = True
        self.algoName = algoName
        self.activeOrderDict = {}  # vtOrderID:order
    
    #----------------------------------------------------------------------
    def updateTick(self, tick):
        """"""
        if not self.active:
            return
        
        self.onTick(tick)
    
    #----------------------------------------------------------------------
    def updateTrade(self, trade):
        """"""
        if not self.active:
            return
        
        self.onTrade(trade)
    
    #----------------------------------------------------------------------
    def updateOrder(self, order):
        """"""
        if not self.active:
            return
        
        # 活动委托需要缓存
        if order.status in STATUS_ACTIVE:
            self.activeOrderDict[order.vtOrderID] = order
        # 结束委托需要移除
        elif order.vtOrderID in self.activeOrderDict:
            del self.activeOrderDict[order.vtOrderID]
        
        self.onOrder(order)
    
    #----------------------------------------------------------------------
    def updateTimer(self):
        """"""
        if not self.active:
            return
        
        self.onTimer()
        
    #----------------------------------------------------------------------
    def stop(self):
        """"""
        self.active = False
        self.cancelAll()
        
        self.onStop()
        
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onTimer(self):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onStop(self):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def subscribe(self, vtSymbol):
        """"""
        self.engine.subscribe(self, vtSymbol)
    
    #----------------------------------------------------------------------
    def buy(self, vtSymbol, price, volume, priceType=None, offset=None):
        """"""
        return self.engine.buy(self, vtSymbol, price, volume, priceType, offset)
    
    #----------------------------------------------------------------------
    def sell(self, vtSymbol, price, volume, priceType=None, offset=None):
        """"""
        return self.engine.sell(self, vtSymbol, price, volume, priceType, offset)
    
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """"""
        self.engine.cancelOrder(self, vtOrderID)
    
    #----------------------------------------------------------------------
    def cancelAll(self):
        """"""
        if not self.activeOrderDict:
            return False
        
        for order in self.activeOrderDict.values():
            self.cancelOrder(order.vtOrderID)
        return True
    
    #----------------------------------------------------------------------
    def getTick(self, vtSymbol):
        """"""
        return self.engine.getTick(self, vtSymbol) 
   
    #----------------------------------------------------------------------
    def getContract(self, vtSymbol):
        """"""
        return self.engine.getContract(self, vtSymbol)    
        
    #----------------------------------------------------------------------
    def roundValue(self, value, change):
        """标准化价格或者数量"""
        if not change:
            return value
        
        n = value / change
        v = round(n, 0) * change
        return v  
    
    #----------------------------------------------------------------------
    def putVarEvent(self, d):
        """更新变量"""
        d['active'] = self.active
        self.engine.putVarEvent(self, d)
        
    #----------------------------------------------------------------------
    def putParamEvent(self, d):
        """更新参数"""
        self.engine.putParamEvent(self, d)
    
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """输出日志"""
        self.engine.writeLog(content, self)
        
        